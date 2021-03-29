/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 14:50:27 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/29 16:51:05 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void execute_pipes2(t_miniast *tree, t_mypipe *pipes)
{
	close(pipes->pipe[0]);
	if (pipes->cmd_no != 0)
	{
		dup2(pipes->temp, STDIN_FILENO);
		close(pipes->temp);
	}
	if (tree->pipe)
	{
		dup2(pipes->pipe[1], STDOUT_FILENO);
		close(pipes->pipe[1]);
	}
	return ;
}

int execute_pip_child(t_miniast *tree, t_mypipe *pipes,
					  char **tabs, t_env **env_list)
{
	signal(SIGTSTP, SIG_DFL);
	execute_pipes2(tree, pipes);
	if (tree->redirection)
		execute_redirection(tree->redirection, g_tty_name);
	if (!tree->pipe && pipes->cmd_no)
		close(pipes->temp);
	if (tree->cmd[0][0] == '!' && tree->cmd[0][1])
	{
		char *line = history_expansion(tree->cmd[0]);
		if (line)
			execute_fc(line);
		ft_strdel(&line);
	}
	else if (check_builtins(tree->cmd[0]))
		execute_blt_with_fork(tree, tabs, env_list);
	else if (tree->cmd[0][0] == '/' ||
			 (tree->cmd[0][0] == '.' && tree->cmd[0][1] == '/'))
		execute_direct(tree->cmd, tabs);
	else if (tree->cmd[0] && env_list)
		execute_undirect(tree->cmd, tabs, env_list);
	return (g_the_status);
}

void checkchild2(int sig)
{
	t_job_ctrl *ptr;
	int status = 0;

	(void)sig;
	ptr = g_jobs_lst;
	while (ptr && ptr->mode != IS_TERMINATED)
	{
		int g_pid = ptr->grp_pid;
		if (waitpid(g_pid * -1, &status, WUNTRACED | WCONTINUED | WNOHANG) > 0)
		{
			if (WIFCONTINUED(status))
				ptr->mode = IS_RUNNING;
			if (WIFSTOPPED(status))
				ptr->mode = IS_SUSPENDED;
			if (WIFEXITED(status))
				delete_node(&g_jobs_lst, ptr->grp_pid);
			else if (WIFSIGNALED(status))
			{
				ptr->status = status;
				ptr->mode = IS_TERMINATED;
			}
		}
		ptr = ptr->next;
	}
}

static void parent_job(t_miniast *tree, t_mypipe *pipes)
{
	close(pipes->pipe[1]);
	if (pipes->temp)
		close(pipes->temp);
	pipes->temp = pipes->pipe[0];
	if (!tree->pipe)
		close(pipes->temp);
	pipes->cmd_no += 1;
}

static void execute_pipes1(t_miniast *tree, t_mypipe *pipes,
						   char **tabs, t_env **env_list)
{
	int fd;

	fd = 0;
	if (pipe(pipes->pipe) == -1)
		return ;
	if ((pipes->pid = fork()) == -1)
		return ;
	if (pipes->g_pid == 0 && pipes->pid > 0)
		pipes->g_pid = pipes->pid;
	if (pipes->pid == 0)
		exit(execute_pip_child(tree, pipes, tabs, env_list));
	else
	{
		if (setpgid(pipes->pid, pipes->g_pid) == -1)
			return ;
		if (!pipes->cmd_no && !(tree->mode & IS_BACKGROUD) && tcsetpgrp((fd = open(ttyname(0), O_RDWR)), pipes->g_pid) == -1)
			return ;
		if (!pipes->cmd_no && !(tree->mode & IS_BACKGROUD))
			close(fd);
		parent_job(tree, pipes);
	}
	return ;
}

void		wait_loop_forground(int is_bg, t_mypipe pipes)
{
	char	**cmd;

	cmd = NULL;
	while (!is_bg && (pipes.pid = waitpid(pipes.g_pid * -1, &(pipes.status), WUNTRACED | WCONTINUED)) != -1)
	{
		if (WIFSTOPPED(pipes.status))
		{
			if (!(cmd = get_job_members(g_tree)))
				return ;
			append_job(cmd, pipes, IS_SUSPENDED);
			print_job_node(pipes.g_pid);
			break ;
		}
		else if (WIFSIGNALED(pipes.status))
		{
			g_the_status = WTERMSIG(pipes.status) + 128;
			print_sigpip_int(pipes.status);
		}
		else if (WIFEXITED(pipes.status))
			g_the_status = WEXITSTATUS(pipes.status);
	}
}

void		job_background(int is_bg, t_mypipe pipes)
{
	char **cmd;

	cmd = NULL;
	if (is_bg > 0)
	{
		if (!(cmd = get_job_members(g_tree)))
			return ;
		append_job(cmd, pipes, IS_BACKGROUD | IS_RUNNING);
		print_job_node(pipes.g_pid);
	}
	close(pipes.temp);
}

int			execute_pipes(t_miniast *tree, char **tabs, t_env **env_list)
{
	t_mypipe	pipes;
	int			is_bg;
	char		*print;

	is_bg = 0;
	print = NULL;
	g_tree = tree;
	if (tree)
		is_bg = tree->mode & IS_BACKGROUD;
	ft_bzero(&pipes, sizeof(t_mypipe));
	while (tree != NULL && tree->cmd[0])
	{
		if (!check_builtins(tree->cmd[0]))
			g_binfile = ft_hashtable(tree->cmd, tabs, &g_hashtable, &print);
		execute_pipes1(tree, &pipes, tabs, env_list);
		if (tree->sep)
			break ;
		ft_strdel_2(&g_binfile, &print);
		tree = tree->pipe;
	}
	ft_strdel_2(&g_binfile, &print);
	wait_loop_forground(is_bg, pipes);
	job_background(is_bg, pipes);
	sig_groupe();
	return (255);
}

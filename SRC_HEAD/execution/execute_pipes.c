/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 14:50:27 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/30 10:40:17 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	parent_job(t_miniast *tree, t_mypipe *pipes)
{
	close(pipes->pipe[1]);
	if (pipes->temp)
		close(pipes->temp);
	pipes->temp = pipes->pipe[0];
	if (!tree->pipe)
		close(pipes->temp);
	pipes->cmd_no += 1;
}

static void	execute_pipes1(t_miniast *tree, t_mypipe *pipes,
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
		if (!pipes->cmd_no && !(tree->mode & IS_BACKGROUD) &&
			tcsetpgrp((fd = open(ttyname(0), O_RDWR)), pipes->g_pid) == -1)
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
	while (!is_bg && (pipes.pid = waitpid(pipes.g_pid * -1, &(pipes.status),
		WUNTRACED | WCONTINUED)) != -1)
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
	char	**cmd;

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

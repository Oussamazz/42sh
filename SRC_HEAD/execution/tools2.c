/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 10:39:45 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/30 10:40:01 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		execute_pipes2(t_miniast *tree, t_mypipe *pipes)
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

int			execute_pip_child(t_miniast *tree, t_mypipe *pipes,
	char **tabs, t_env **env_list)
{
	char *line;

	line = NULL;
	signal(SIGTSTP, SIG_DFL);
	execute_pipes2(tree, pipes);
	if (tree->redirection)
		execute_redirection(tree->redirection, g_tty_name);
	if (!tree->pipe && pipes->cmd_no)
		close(pipes->temp);
	if (tree->cmd[0][0] == '!' && tree->cmd[0][1])
	{
		line = history_expansion(tree->cmd[0]);
		if (line)
			execute_fc(line);
		ft_strdel(&line);
	}
	else if (check_builtins(tree->cmd[0]))
		execute_blt_with_fork(tree, env_list);
	else if (tree->cmd[0][0] == '/' ||
			(tree->cmd[0][0] == '.' && tree->cmd[0][1] == '/'))
		execute_direct(tree->cmd, tabs);
	else if (tree->cmd[0] && env_list)
		execute_undirect(tree->cmd, tabs, env_list);
	return (g_the_status);
}

void		checkchild2(int sig)
{
	t_job_ctrl	*ptr;
	int			status;

	(void)sig;
	status = 0;
	ptr = g_jobs_lst;
	while (ptr && ptr->mode != IS_TERMINATED)
	{
		g_pid = ptr->grp_pid;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg_blt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 14:35:16 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/29 19:06:05 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int		size_of_lst(t_job_ctrl *lst)
{
	int			size;
	t_job_ctrl	*ptr;

	ptr = g_jobs_lst;
	(void)lst;
	size = 0;
	while (ptr)
	{
		size++;
		ptr = ptr->next;
	}
	return (size);
}

static int		get_job_id(char **cmd)
{
	int			size;

	size = 0;
	if ((size = get_arr_size(cmd)) == 1)
		return (0);
	if (size > 1)
	{
		if (cmd[1] && cmd[1][0] == '%' && cmd[1][1] == '-' && !cmd[1][2])
			return (size_of_lst(g_jobs_lst) - 1);
		else if (cmd[1] && cmd[1][0] == '%' && (cmd[1][1] == '+' ||
			cmd[1][1] == '%') && !cmd[1][2])
			return (0);
		else if (cmd[1] && cmd[1][0] == '%' && ft_isdigit(cmd[1][1]))
			return (ft_atoi(&cmd[1][1]));
	}
	return (-1);
}

int				fg_init(char **cmd, t_f_g *fg)
{
	(*fg).job_id = get_job_id(cmd);
	(*fg).ptr = g_jobs_lst;
	(*fg).fd = 0;
	if (((*fg).fd = open(ttyname(0), O_RDWR)) == -1)
		return (1);
	signal(SIGCHLD, NULL);
	return (0);
}

void			fg_wait_check(t_f_g *fg)
{
	while ((waitpid((*fg).ptr->grp_pid * -1,
					&(*fg).status, WUNTRACED | WCONTINUED)) > 0)
	{
		if (WIFSTOPPED((*fg).status))
		{
			(*fg).ptr->mode = IS_SUSPENDED;
			break ;
		}
		else if (WIFEXITED((*fg).status))
			delete_node(&g_jobs_lst, (*fg).ptr->grp_pid);
		else if (WIFSIGNALED((*fg).status))
			delete_node(&g_jobs_lst, (*fg).ptr->grp_pid);
	}
}

int				fg_blt(char **cmd)
{
	t_f_g		fg;

	if (fg_init(cmd, &fg))
		return (1);
	while (fg.ptr && fg.job_id >= 0)
	{
		if (((fg.ptr->c == '+' && !fg.job_id) ||
			(fg.ptr->job_id == fg.job_id && fg.job_id)))
		{
			if (tcsetpgrp(fg.fd, fg.ptr->grp_pid) == -1)
			{
				close(fg.fd);
				return (1);
			}
			close(fg.fd);
			kill(fg.ptr->grp_pid * -1, SIGCONT);
			fg.ptr->mode = IS_FOURGROUND | IS_RUNNING;
			fg_wait_check(&fg);
			sig_groupe();
			break ;
		}
		fg.ptr = fg.ptr->next;
	}
	signal(SIGCHLD, checkchild2);
	return (0);
}

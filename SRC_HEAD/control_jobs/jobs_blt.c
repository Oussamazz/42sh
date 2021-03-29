/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_blt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 17:36:52 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/29 16:13:20 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	get_options(char **cmd)
{
	int		i;
	int		options;

	options = -1;
	if (!cmd)
		return (options);
	if (cmd)
	{
		if (cmd[1] && cmd[1][0] == '-' && cmd[1][1])
		{
			i = 1;
			while (cmd[1][i + 1])
				i++;
			cmd[1][i] == 'l' ? options = JOB_DETAILS : 0;
			cmd[1][i] == 'p' ? options = JOB_PIDS : 0;
			cmd[1][i] == 'r' ? options = JOB_RUNNING : 0;
		}
		else if (!cmd[1])
			options = JOB_MAIN;
	}
	return (options);
}

void		jobs_blt(char **cmd)
{
	int			options;
	t_job_ctrl	*ptr;
	t_job_ctrl	*next;

	ptr = g_jobs_lst;
	if ((options = get_options(cmd)) < 0)
		return (ft_putendl_fd("42sh: usage: jobs [-lpr]", 2));
	while (ptr)
	{
		next = ptr->next;
		if (ptr->mode & IS_TERMINATED)
		{
			details_infos(ptr);
			delete_node(&g_jobs_lst, ptr->grp_pid);
		}
		else if (options & JOB_MAIN)
			main_infos(ptr);
		else if (options & JOB_PIDS)
			pid_infos(ptr);
		else if (options & JOB_DETAILS)
			details_infos(ptr);
		else if ((options & JOB_RUNNING) && (ptr->mode & IS_RUNNING))
			main_infos(ptr);
		ptr = next;
	}
}

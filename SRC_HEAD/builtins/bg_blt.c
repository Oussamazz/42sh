/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_blt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 16:02:16 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/29 19:02:59 by oelazzou         ###   ########.fr       */
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

int				bg_blt(char **cmd)
{
	t_job_ctrl	*ptr;
	int			job_id;

	ptr = g_jobs_lst;
	if (!ptr)
	{
		ft_putendl_fd("bg: no current job", 2);
		g_the_status = 1;
		return (1);
	}
	job_id = get_job_id(cmd);
	while (ptr)
	{
		if ((ptr->c == '+' && job_id == 0 && (ptr->mode & IS_SUSPENDED)) ||
			(ptr->job_id == job_id && (ptr->mode & IS_SUSPENDED)))
		{
			ptr->mode = IS_RUNNING;
			kill(ptr->grp_pid * -1, SIGCONT);
			break ;
		}
		ptr = ptr->next;
	}
	return (0);
}

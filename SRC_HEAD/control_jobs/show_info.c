/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 15:51:35 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/29 16:16:30 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		main_infos(t_job_ctrl *ptr)
{
	if (ptr)
	{
		ft_putchar_fd('[', 1);
		ft_putnbr_fd(ptr->job_id, 1);
		ft_putstr_fd("]", 1);
		ft_putchar_fd(ptr->c, 1);
		ft_putstr_fd("  ", 1);
		if ((ptr->mode & IS_RUNNING) || (ptr->mode & IS_BACKGROUD))
			ft_putstr_fd("Running\t\t\t", 1);
		else if (ptr->mode & IS_TERMINATED)
			ft_putstr_fd("Terminated\t\t\t", 1);
		else if (ptr->mode & IS_SUSPENDED)
			ft_putstr_fd("Stopped\t\t\t", 1);
		if (ptr->cmd)
			print_arr(ptr->cmd);
	}
}

void		details_infos(t_job_ctrl *ptr)
{
	if (ptr)
	{
		ft_putchar_fd('[', 1);
		ft_putnbr_fd(ptr->job_id, 1);
		ft_putstr_fd("]", 1);
		ft_putchar_fd(ptr->c, 1);
		ft_putstr_fd("  ", 1);
		ft_putnbr_fd(ptr->grp_pid, 1);
		ft_putchar_fd(' ', 1);
		if ((ptr->mode & IS_RUNNING) || (ptr->mode & IS_BACKGROUD))
			ft_putstr_fd("Running\t\t\t", 1);
		else if (ptr->mode & IS_TERMINATED)
		{
			ft_putstr_fd("killed: ", 1);
			ft_putnbr_fd(WTERMSIG(ptr->status), 1);
			ft_putstr_fd("\t\t", 1);
		}
		else if (ptr->mode & IS_SUSPENDED)
			ft_putstr_fd("Stopped\t\t\t", 1);
		if (ptr->cmd)
			print_arr(ptr->cmd);
	}
}

void		pid_infos(t_job_ctrl *ptr)
{
	if (ptr)
	{
		ft_putnbr_fd(ptr->grp_pid, 1);
		ft_putchar_fd('\n', 1);
	}
}

void		print_job_node(int g_pid)
{
	t_job_ctrl	*ptr;

	ptr = g_jobs_lst;
	while (ptr)
	{
		if (ptr->grp_pid == g_pid)
		{
			ft_putchar_fd('[', 1);
			ft_putnbr_fd(ptr->job_id, 1);
			ft_putstr_fd("] ", 1);
			ft_putnbr_fd(ptr->grp_pid, 1);
			ft_putchar_fd('\n', 1);
			break ;
		}
		ptr = ptr->next;
	}
}

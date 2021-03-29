/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_jobs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 14:51:37 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/29 16:15:36 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		assing(void)
{
	t_job_ctrl	*ptr;

	ptr = g_jobs_lst;
	while (ptr)
	{
		if (ptr->next && ptr->next->c == '+')
		{
			ptr->c = '-';
			break ;
		}
		ptr = ptr->next;
	}
}

void		init_signs(void)
{
	t_job_ctrl *ptr;

	ptr = g_jobs_lst;
	while (ptr)
	{
		ptr->c = ' ';
		ptr = ptr->next;
	}
}

void		append_job(char **arr, t_mypipe pipe, int mode)
{
	t_job_ctrl	*last;
	t_job_ctrl	*ret;

	(void)arr;
	last = g_jobs_lst;
	if (!(ret = (t_job_ctrl *)ft_memalloc(sizeof(t_job_ctrl))))
		return ;
	init_signs();
	ret->cmd = arr;
	ret->grp_pid = pipe.g_pid;
	ret->status = pipe.status;
	ret->c = '+';
	ret->mode |= mode;
	ret->next = NULL;
	if (last == NULL)
	{
		ret->job_id = 1;
		g_jobs_lst = ret;
		return ;
	}
	while (last->next)
		last = last->next;
	last->c = '-';
	ret->job_id = last->job_id + 1;
	last->next = ret;
}

t_job_ctrl	*dup_job(t_job_ctrl *ptr)
{
	t_job_ctrl	*ret;

	if (!(ret = (t_job_ctrl *)ft_memalloc(sizeof(t_job_ctrl))))
		return (NULL);
	ret->c = ' ';
	ret->cmd = ptr->cmd;
	ret->grp_pid = ptr->grp_pid;
	ret->job_id = ptr->job_id;
	ret->mode = IS_TERMINATED;
	ret->status = ptr->status;
	ret->next = NULL;
	return (ret);
}

int			delete_node(t_job_ctrl **head_ref, int g_pid)
{
	t_job_ctrl *temp;
	t_job_ctrl *prev;

	temp = *head_ref;
	if (temp != NULL && temp->grp_pid == g_pid)
	{
		*head_ref = temp->next;
		ft_free_arr(temp->cmd);
		free(temp);
		return (1);
	}
	while (temp != NULL && temp->grp_pid != g_pid)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return (0);
	prev->next = temp->next;
	prev->c = '+';
	ft_free_arr(temp->cmd);
	free(temp);
	assing();
	return (1);
}

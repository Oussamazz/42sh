/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 15:51:52 by oelazzou          #+#    #+#             */
/*   Updated: 2021/01/31 15:54:27 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	_init(void)
{
	if (!g_jobs)
	{
		if (!(g_jobs = (t_job_ctrl*)ft_memalloc(sizeof(t_job_ctrl))))
			return ;
		g_jobs->pid = getpid();
		g_jobs->next = NULL;
	}
	return ;
}

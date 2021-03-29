/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_jobs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 14:35:08 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/29 15:46:24 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	print_sigpip_int(int status)
{
	if (WTERMSIG(status) != SIGPIPE)
	{
		if (WTERMSIG(status) != SIGINT)
		{
			ft_putstr_fd("Terminated with Signal: ", 1);
			ft_putnbr_fd(WTERMSIG(status), 1);
		}
		ft_putendl_fd("", 1);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 17:32:14 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/25 15:24:15 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	blt_echo(char **cmd)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	if (cmd[1] && ft_strequ(cmd[1], "-n"))
	{
		i++;
		flag = 1;
	}
	while (cmd[++i] != NULL)
	{
		if (ft_strequ(cmd[i], "?"))
			ft_putnbr(g_the_status);
		else
			ft_putstr_fd(cmd[i], STDOUT_FILENO);
		if (cmd[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (!flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	g_the_status = 0;
	// sleep(1000);
	return ;
}

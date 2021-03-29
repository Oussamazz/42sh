/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_blt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 18:51:39 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/29 18:51:13 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	free_(void)
{
	ft_free_history();
	ft_tabfree();
	ft_listfree();
	ft_free_his(&g_his);
}

void	exit_blt(char **cmd)
{
	int cmd_no;

	if ((cmd_no = check_args_no(cmd)) > 2)
	{
		ft_putendl_fd("Too many arguments", 2);
		g_the_status = 1;
	}
	else if (cmd_no == 2 || cmd_no == 1)
	{
		if (cmd[1])
		{
			if (ft_isnumber(cmd[1]))
			{
				free_();
				exit(ft_atoi(cmd[1]));
			}
			g_the_status = 1;
			return (ft_putendl_fd("42sh: exit: numeric argument required", 2));
		}
		else
		{
			free_();
			exit(0);
		}
	}
}

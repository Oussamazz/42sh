/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_blt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 18:51:39 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/25 16:15:44 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	exit_blt(char **cmd)
{
	int cmd_no;
	int exit_value;

	exit_value = 0;
	if ((cmd_no = check_args_no(cmd)) > 2)
	{
		ft_putendl_fd("Too many arguments", 2);
		g_the_status = 1;
		return ;
	}
	else if (cmd_no >= 1)
	{
		// int ft_isnumber(char *str)
		ft_putendl("exit");
		ft_free_history();
		ft_tabfree();
		ft_listfree();
		ft_free_his(&g_his);
		if (cmd[1])
			exit(ft_atoi(cmd[1]));
		else
			exit(0);
	}
}

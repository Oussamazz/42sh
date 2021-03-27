/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 17:32:14 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/27 11:16:21 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int check_redirection_out(t_redir *redirection)
{
	while (redirection)
	{
		if (redirection->next == NULL)
			break ;
		redirection = redirection->next;
	}
	if (redirection->sym && ft_strequ(redirection->sym, ">&-"))
		return (0);
	return (1);
}

void	blt_echo(char **cmd, t_redir *redirection)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	if (redirection && !check_redirection_out(redirection))
	{
		g_the_status = 1;
		return (ft_putendl_fd("42sh: echo: write error: Bad file descriptor", 2));
	}
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
	return ;
}

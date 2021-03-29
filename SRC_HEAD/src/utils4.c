/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 17:42:54 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/29 16:27:14 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				str_is_blank(char *buffer)
{
	if (ft_strequ(buffer, "fc") || *buffer == '!')
		return (1);
	while (*buffer)
	{
		if (!is_blank(*buffer))
			return (0);
		buffer++;
	}
	return (1);
}

int				check_builtins_nfrk(char *cmd_name)
{
	if (ft_strequ(cmd_name, "alias") || ft_strequ(cmd_name, "unalias") ||
		ft_strequ(cmd_name, "fc") || ft_strequ(cmd_name, "type") ||
		ft_strequ(cmd_name, "exit") || ft_strequ(cmd_name, "jobs") ||
		ft_strequ(cmd_name, "fg") || ft_strequ(cmd_name, "bg")
		|| ft_strequ(cmd_name, "cd") || ft_strequ(cmd_name, "unset") ||
		ft_strequ(cmd_name, "export") || ft_strequ(cmd_name, "hash") ||
		ft_strequ(cmd_name, "test") || ft_strequ(cmd_name, "set"))
		return (1);
	return (0);
}

int				ft_str_is_digit(char *lfd)
{
	int			i;

	i = 0;
	if (lfd)
	{
		while (lfd[i])
		{
			if (!ft_isdigit(lfd[i]))
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void			ft_reset_fd(char *tty_name, int file_d)
{
	int			fd;

	fd = 0;
	(void)tty_name;
	(void)file_d;
	if ((fd = open(ttyname(0), O_RDWR)) == -1)
		return ;
	dup2(fd, STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	dup2(fd, STDERR_FILENO);
	close(fd);
}

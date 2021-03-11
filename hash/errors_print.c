/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 06:11:13 by oelazzou           #+#    #+#             */
/*   Updated: 2021/01/20 16:24:40 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void		ft_hash_error(char *str)
{
	if (str)
	{
		ft_putstr_fd("42sh: hash: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": invalid option", 2);
		ft_putstr_fd("42sh: usage: ", 2);
		ft_putendl_fd("hash [-lr] [-p pathname] [-dt] [name ...]", 2);
	}
	else
	{
		ft_putendl_fd("42sh: hash: -p: option requires an argument", 2);
		ft_putstr_fd("42sh: usage: ", 2);
		ft_putendl_fd("hash [-lr] [-p pathname] [-dt] [name ...]", 2);
	}
}

void		l_flag_error(char *str)
{
	ft_putstr_fd("42sh: hash: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": not found\n", 2);
}

void		l_flag_print(char *value, char *key)
{
	ft_putstr("builtin hash -p ");
	ft_putstr(value);
	ft_putchar(' ');
	ft_putendl(key);
}

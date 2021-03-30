/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_fc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <yabakhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 17:36:37 by yabakhar          #+#    #+#             */
/*   Updated: 2021/03/29 18:08:16 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void		ft_calc_debut_fin(t_opt *opt)
{
	opt->debut = ((ft_abs(opt->debut) > opt->sizeoflist)
		|| (opt->debut == 0)) ? (-1) : opt->debut;
	opt->fin = ((ft_abs(opt->fin) > opt->sizeoflist)
		|| (opt->fin == 0)) ? (-1) : opt->fin;
	opt->debut = (opt->debut < 0) ?
		(opt->sizeoflist - ft_abs(opt->debut)) : opt->debut;
	opt->fin = (opt->fin < 0) ? (opt->sizeoflist - ft_abs(opt->fin)) : opt->fin;
}

int			ft_get_debut_fin(t_opt *opt, char **hold)
{
	if (opt->count >= 1)
	{
		if (!(get_index_fc(hold[opt->check], &opt->debut)))
			return (0);
		if (opt->count > 1)
			if (!(get_index_fc(hold[opt->check + 1], &opt->fin)))
				return (0);
		return (1);
	}
	return (0);
}

void		opt_error(char c)
{
	ft_putstr("42sh: fc: -");
	ft_putchar(c);
	ft_putendl(" : invalid option");
	ft_putstr("fc: usage: fc [-e ename] [-lnr] [first] [last]");
	ft_putendl(" or fc -s [pat=rep] [command]");
}

int			ft_isnumber(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int			check_index_fc(char *str, int *index)
{
	if ((str[0] == '-') && (ft_isnumber(str + 1)))
	{
		(*index) = ft_atoi(str);
		return (1);
	}
	else if (ft_isnumber(str))
	{
		(*index) = ft_atoi(str);
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_fc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <yabakhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 18:08:11 by yabakhar          #+#    #+#             */
/*   Updated: 2021/03/29 18:12:11 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int			check_isnbrvalide(char *str)
{
	if ((str[0] == '-') && (ft_isnumber(str + 1)))
		return (1);
	else if (ft_isnumber(str))
		return (1);
	return (0);
}

int			check_error_fc(t_opt *opt)
{
	if (!opt->count)
	{
		ft_putendl("fc: argument expected: -e");
		return (0);
	}
	else if (opt->count > 3)
	{
		ft_putendl("fc: too many arguments");
		return (0);
	}
	return (1);
}

int			check_debut_fin_e(t_opt *opt, char **hold)
{
	if (!check_error_fc(opt))
		return (0);
	else if (opt->count <= 3)
	{
		if (!preparer_path(hold[opt->check], opt))
			return (0);
		if (opt->count == 1)
			opt->debut = -1;
		else if (opt->count >= 2)
		{
			if (!(get_index_fc(hold[opt->check + 1], &opt->debut)))
				return (0);
			if (opt->count > 2)
				if (!(get_index_fc(hold[opt->check + 2], &opt->fin)))
					return (0);
		}
		return (1);
	}
	return (0);
}

void		count_arg_fc(t_opt *opt)
{
	if (opt->check == 0)
		opt->check = opt->i;
	opt->count += 1;
}

int			check_opt(t_opt *opt, char *hold)
{
	int		i;

	if (check_isnbrvalide(hold))
	{
		count_arg_fc(opt);
		return (1);
	}
	else if (hold[0] == '-')
	{
		i = 1;
		while (hold[i])
		{
			if (!(check_valide_opt(opt, hold, i)))
				return (0);
			i++;
		}
	}
	else
		count_arg_fc(opt);
	return (1);
}

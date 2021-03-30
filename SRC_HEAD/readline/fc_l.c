/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_l.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <yabakhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 00:09:39 by yabakhar          #+#    #+#             */
/*   Updated: 2021/03/29 17:37:05 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void		ft_affiche_tab_l(char **result, int size, t_opt *opt, int sin)
{
	int		k;

	k = 0;
	if (opt->r)
	{
		while (size)
		{
			if (!opt->n)
				ft_putnbr(opt->fin);
			ft_putchar('\t');
			ft_putendl(result[--size]);
			opt->fin = opt->fin - sin;
		}
	}
	else if (!opt->r)
	{
		while (size > k)
		{
			if (!opt->n)
				ft_putnbr(opt->debut);
			ft_putchar('\t');
			ft_putendl(result[k++]);
			opt->debut = opt->debut + sin;
		}
	}
}

int			ft_get_debut_fin_l(t_opt *opt, char **hold)
{
	if (opt->count == 0)
	{
		opt->debut = -16;
		opt->fin = 0;
	}
	else
	{
		if (!ft_get_debut_fin(opt, hold))
			return (0);
	}
	ft_calc_debut_fin(opt);
	return (1);
}

void		ft_calc_range_of_debut_fin(t_opt *opt, int *size, char ***result)
{
	t_node	*history;
	int		i;

	i = 0;
	history = add_to_history(NULL);
	*size = opt->debut - opt->fin;
	*size += (((*size > 0) ? 1 : -1) * (opt->count >= 0));
	get_index_in_list(&history, opt->debut);
	(*result) = ft_memalloc(sizeof(char *) * (ft_abs(*size) + 1));
	while (1)
	{
		(*result)[ft_abs(i)] = history->content;
		history = (*size > 0) ? history->prev : history->next;
		i += (*size > 0) ? 1 : -1;
		if (!history || i == *size)
			break ;
	}
}

int			fc_l(t_opt *opt, char **hold)
{
	char	**result;
	int		size;

	if (ft_get_debut_fin_l(opt, hold))
	{
		ft_calc_range_of_debut_fin(opt, &size, &result);
		ft_affiche_tab_l(result, ft_abs(size), opt, ft_sin(size));
		free(result);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_e.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 00:09:39 by yabakhar          #+#    #+#             */
/*   Updated: 2020/10/19 17:35:42 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void		ft_affiche_tab_e(char **result, int size, t_opt *opt, int sin)
{
	int		k;
	int		fd;

	k = 0;
	if ((fd = open(PATH_FC_FILE, O_RDWR | O_TRUNC | O_CREAT, 00600)) == -1)
		return ;
	if (opt->r)
	{
		while (size)
		{
			ft_putendl_fd(result[--size], fd);
			opt->fin = opt->fin - sin;
		}
	}
	else if (!opt->r)
	{
		while (size > k)
		{
			ft_putendl_fd(result[k++], fd);
			opt->debut = opt->debut + sin;
		}
	}
	close(fd);
}

int			fc_e(t_opt *opt, char **hold, t_node *history)
{
	int		size;
	char	**result;
	int		fd;

	if ((fd = open(PATH_FC_FILE, O_RDWR | O_TRUNC | O_CREAT, 00600)) == -1)
		return (0);
	if (check_debut_fin_e(opt, hold))
	{
	 	if ( opt->count == 1 || opt->count == 2)
		{
			opt->debut = ((ft_abs(opt->debut) > opt->sizeoflist) || (opt->debut == 0)) ? (-1) : opt->debut;
			opt->debut = (opt->debut < 0) ? (opt->sizeoflist - ft_abs(opt->debut)) : opt->debut;
			get_index_in_list(&history, opt->debut);
			ft_putendl(history->content);
		}
		else if (opt->count == 3)
		{
			ft_calc_debut_fin(opt);
			ft_calc_range_of_debut_fin(opt, &size, &result);
			ft_affiche_tab_e(result, ft_abs(size), opt, ft_sin(size));
		}
		execute_commande_fc(PATH_FC_FILE);
		return (1);
	}
	return (0);
}

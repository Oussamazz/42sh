/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_e.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <yabakhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 00:09:39 by yabakhar          #+#    #+#             */
/*   Updated: 2021/03/29 18:34:44 by yabakhar         ###   ########.fr       */
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

int			fc_e(t_opt *opt, char **hold)
{
	int		fd;

	if ((fd = open(PATH_FC_FILE, O_RDWR | O_TRUNC | O_CREAT, 00600)) == -1)
		return (0);
	if (check_debut_fin_e(opt, hold))
	{
		if (opt->count == 1 || opt->count == 2)
			fc_one_argement(fd, opt);
		else if (opt->count == 3)
			fc_many_argement(opt);
		execute_open_file(opt->editeur);
		execute_commande_fc(PATH_FC_FILE);
		return (1);
	}
	return (0);
}

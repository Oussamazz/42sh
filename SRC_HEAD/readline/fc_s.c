/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_s.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <yabakhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 16:04:07 by yabakhar          #+#    #+#             */
/*   Updated: 2021/03/29 18:45:34 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		fc_one_argement(int fd, t_opt *opt)
{
	t_node	*history;

	history = add_to_history(NULL);
	opt->debut = ((ft_abs(opt->debut) > opt->sizeoflist) ||
		(opt->debut == 0)) ? (-1) : opt->debut;
	opt->debut = (opt->debut < 0) ?
		(opt->sizeoflist - ft_abs(opt->debut)) : opt->debut;
	get_index_in_list(&history, opt->debut);
	ft_putendl_fd(history->content, fd);
	close(fd);
}

void		fc_many_argement(t_opt *opt)
{
	int		size;
	char	**result;

	size = 0;
	result = NULL;
	ft_calc_debut_fin(opt);
	ft_calc_range_of_debut_fin(opt, &size, &result);
	ft_affiche_tab_e(result, ft_abs(size), opt, ft_sin(size));
	free(result);
}

void		fc_without_flag(t_opt *opt, char **hold)
{
	t_node	*history;
	int		fd;

	if ((fd = open(PATH_FC_FILE, O_RDWR | O_TRUNC | O_CREAT, 00600)) == -1)
		return ;
	history = add_to_history(NULL);
	if (!opt->count)
	{
		if (history->next)
			ft_putendl_fd(history->next->content, fd);
		close(fd);
		execute_open_file(opt->editeur);
		execute_commande_fc(PATH_FC_FILE);
	}
	if (ft_get_debut_fin(opt, hold))
	{
		if (opt->count == 1)
			fc_one_argement(fd, opt);
		else if (opt->count >= 2)
			fc_many_argement(opt);
		execute_open_file(opt->editeur);
		execute_commande_fc(PATH_FC_FILE);
	}
}

void		fc_s(t_opt *opt, char **hold)
{
	t_node	*history;
	int		fd;
	char	*str;

	str = NULL;
	if ((fd = open(PATH_FC_FILE, O_RDWR | O_TRUNC | O_CREAT, 00600)) == -1)
		return ;
	history = add_to_history(NULL);
	if (!opt->count)
	{
		if (history->next)
			ft_putstr_fd(history->next->content, fd);
		execute_open_file(opt->editeur);
		execute_commande_fc(PATH_FC_FILE);
	}
	else if (opt->count >= 1)
	{
		if (!(get_index_fc(hold[opt->check], &opt->debut)))
			return ;
		str = get_content_in_list(opt->debut);
		ft_putstr_fd(str, fd);
		ft_strdel(&str);
		execute_open_file(opt->editeur);
		execute_commande_fc(PATH_FC_FILE);
	}
}

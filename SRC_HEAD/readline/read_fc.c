/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <yabakhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 00:09:39 by yabakhar          #+#    #+#             */
/*   Updated: 2021/03/29 18:32:17 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int			check_valide_opt(t_opt *opt, char *hold, int i)
{
	if (hold[i] == 'l' && !opt->check)
		opt->l = 1;
	else if (hold[i] == 'n' && !opt->check)
		opt->n = 1;
	else if (hold[i] == 'e' && !opt->check)
		opt->e = 1;
	else if (hold[i] == 's' && !opt->check)
		opt->s = 1;
	else if (hold[i] == 'r' && !opt->check)
		opt->r = 1;
	else
	{
		if (!ft_strchr("lners", hold[i]) && !opt->check)
		{
			opt_error(hold[i]);
			return (0);
		}
		else
			count_arg_fc(opt);
	}
	return (1);
}

void		execute_commande_fc(const char *file)
{
	char	*line;
	int		fd;
	char	*rest;

	rest = ft_strdup("");
	line = NULL;
	if ((fd = open(file, O_RDWR | O_CREAT, 00600)) == -1)
		return ;
	while (get_next_line(fd, &line) > 0)
	{
		line = ft_freejoin(line, ";", 0);
		rest = ft_freejoin(rest, line, 2);
	}
	close(fd);
	if (rest && *rest)
		execute_fc(rest);
	ft_strdel(&rest);
}

void		execute_open_file(char *editeur)
{
	char	*line;

	if (!editeur)
		editeur = "vim";
	line = ft_strjoin_four(editeur, " ", PATH_FC_FILE, "");
	if (line)
		execute_fc(line);
	ft_strdel(&(line));
}

void		ft_handel_fc(t_opt *opt, char **hold)
{
	if (opt->s == 1)
		fc_s(opt, hold);
	else if (opt->l == 1)
		fc_l(opt, hold);
	else if (opt->e == 1)
		fc_e(opt, hold);
	else if ((opt->i - opt->count) == 1 || opt->n || opt->r)
		fc_without_flag(opt, hold);
}

void		parce_param_fc(char **hold)
{
	t_opt	opt;
	t_node	*history;

	ft_bzero(&opt, sizeof(t_opt));
	history = add_to_history(NULL);
	opt.sizeoflist = calc_list(history);
	while (++opt.i < (ft_calc(hold) + 1))
	{
		if (!(check_opt(&opt, hold[opt.i])))
			return ;
	}
	ft_handel_fc(&opt, hold);
}

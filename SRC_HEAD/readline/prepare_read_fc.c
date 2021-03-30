/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_read_fc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <yabakhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 18:04:39 by yabakhar          #+#    #+#             */
/*   Updated: 2021/03/29 18:09:32 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int			ft_calc(char **hold)
{
	int		i;

	i = 0;
	while (hold[i])
		i++;
	if (i > 0)
		i--;
	return (i);
}

int			index2_fc(char *str, int *index)
{
	t_node	*list;
	int		i;

	list = add_to_history(NULL);
	i = 0;
	while (list)
	{
		if (!ft_strncmp(str, list->content, ft_strlen(str)))
			(*index) = i;
		list = list->next;
		i++;
	}
	if ((*index) > 0)
		return (1);
	else
		return (0);
}

int			get_index_fc(char *hold, int *index)
{
	if (!(check_index_fc(hold, index)) && !(index2_fc(hold, index)))
	{
		ft_putendl("42sh: fc: history specification out of range");
		return (0);
	}
	return (1);
}

int			preparer_path(char *editeur, t_opt *opt)
{
	char	*path;

	path = ft_strjoin("/usr/bin/", editeur);
	if (access(path, F_OK) == 0)
	{
		if (!ft_strcmp("vim", editeur) || !ft_strcmp("vi", editeur) ||
			!ft_strcmp("nano", editeur) || !ft_strcmp("emacs", editeur))
		{
			opt->editeur = editeur;
			ft_strdel(&path);
			return (1);
		}
	}
	else
	{
		ft_putstr("42sh: command not found: ");
		ft_putendl(editeur);
		ft_strdel(&path);
		return (0);
	}
	ft_strdel(&path);
	return (0);
}

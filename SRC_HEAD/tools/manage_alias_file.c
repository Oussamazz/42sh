/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_alias_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:19:45 by afaragi           #+#    #+#             */
/*   Updated: 2021/03/29 16:23:17 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		add_to_alias_file(char *line, t_alias **alias)
{
	t_alias	*new;
	char	*tmp;
	char	**check;

	tmp = ft_strtrim(line);
	if (tmp && tmp[0] && tmp[0] != '=' &&
	counter(check = ft_strsplit(line, '=')) == 2 &&
	checker_alias(check) && !check_alias_repeate(check[0], (*alias)))
	{
		new = alias_create(check[0], check[1]);
		*alias = alias_lst_adder(alias, new);
	}
	else
		ft_putendl_fd("alias : Wrong Fromat Or Already added", 2);
	free2dm(&check);
	ft_strdel(&tmp);
}

void		add_alias_list_to_file(t_alias *alias)
{
	int		file;

	file = open("/Users/afaragi/.biggyrc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (alias)
	{
		while (alias)
		{
			ft_putstr_fd(alias->name, file);
			ft_putstr_fd("=", file);
			ft_putendl_fd(alias->value, file);
			alias = alias->next;
		}
	}
}

int			isthere_alnum(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int			checker_alias(char **str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (str)
	{
		while (str[i])
		{
			if (!isthere_alnum(str[i]))
				return (0);
			i++;
		}
	}
	return (1);
}

int			if_i_found_it(t_alias *pr, t_alias *ptr, t_alias **al, char *str)
{
	if (ft_strcmp(ptr->name, str) == 0)
	{
		if (pr)
			pr->next = ptr->next;
		else
			*al = ptr->next;
		ft_one_alias_del(&ptr, del);
		return (-1);
	}
	return (1);
}

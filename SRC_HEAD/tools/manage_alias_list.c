/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_alias_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:14:57 by afaragi           #+#    #+#             */
/*   Updated: 2021/03/29 16:26:16 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		get_value_from_list(char *line, t_alias *alias, int flag)
{
	while (alias)
	{
		if (flag)
		{
			ft_putstr_fd(alias->name, 1);
			ft_putstr_fd("='", 1);
			ft_putstr_fd(alias->value, 1);
			ft_putendl_fd("'", 1);
		}
		else if (!ft_strcmp(alias->name, line))
			ft_putendl_fd(alias->value, 1);
		alias = alias->next;
	}
	if (!flag)
		free(line);
}

void		create_alias_list(void)
{
	t_alias	*alias;
	int		file;
	char	*buff;
	char	**cmp;

	buff = NULL;
	cmp = NULL;
	file = open("/Users/afaragi/.biggyrc", O_RDONLY | O_CREAT, 0644);
	while (get_next_line(file, &buff) > 0)
	{
		if (((counter(cmp = ft_strsplit(buff, '=')) != 2 ||
			!checker_alias(cmp))) || !cmp)
		{
			free2dm(&cmp);
			ft_strdel(&buff);
			continue ;
		}
		alias = alias_create(cmp[0], cmp[1]);
		g_alias = alias_lst_adder(&g_alias, alias);
		free2dm(&cmp);
		ft_strdel(&buff);
	}
	ft_strdel(&buff);
	close(file);
}

t_alias		*alias_create(char *name, char *value)
{
	t_alias	*list;

	if (!(list = (t_alias *)(ft_memalloc(sizeof(t_alias)))))
		return (NULL);
	if (name)
	{
		list->name = ft_strdup(name);
		if (value)
			list->value = ft_strdup(value);
	}
	return (list);
}

t_alias		*alias_lst_adder(t_alias **old, t_alias *new)
{
	t_alias	*head;

	head = *old;
	if (!head)
	{
		*old = new;
		return (new);
	}
	else
	{
		while (head->next)
			head = head->next;
		head->next = new;
		new = NULL;
		return (*old);
	}
}

void		delete_alias_var(t_alias **alias, char **str)
{
	t_alias	*ptr;
	t_alias	*previous;
	int		i;

	i = 1;
	if (!str[1])
		ft_putstr_fd("unalias: Too few arguments.\n", 2);
	else
	{
		while (str[i])
		{
			ptr = *alias;
			previous = NULL;
			while (ptr && ptr->name)
			{
				if (if_i_found_it(previous, ptr, alias, str[i]) == -1)
					break ;
				previous = ptr;
				ptr = ptr->next;
			}
			i++;
		}
	}
}

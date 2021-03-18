/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_tools2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 05:58:20 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/18 12:17:01 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		del_list_mini(t_ht **list, int len)
{
	t_ht	*current;
	t_ht	*next;

	current = *list;
	while (current)
	{
		if (current->next && current->next->hits != 0 && len > 2)
		{
			next = current->next->next;
			free_node(&current);
			current = next;
		}
		else if (len == 2)
		{
			next = current->next->next;
			free_node(&current);
			current = next;
		}
		current = current->next;
	}
}

void		search_hash_mini(t_hash **h_table, char **args)
{
	int		i;
	int		slot;
	t_ht	*current;
	t_hash	*hashtable;

	i = 1;
	hashtable = *h_table;
	while (args[++i])
	{
		slot = hash_function(args[i]);
		current = hashtable->list[slot];
		if (!current)
			l_flag_error(args[i]);
		while (current)
		{
			if (ft_strcmp(args[i], current->key) == 0)
			{
				ft_putstr_fd(args[i], 1);
				ft_putstr_fd("     ", 1);
				ft_putendl_fd(current->value, 1);
				break ;
			}
			current = current->next;
		}
	}
}

t_ht		*hash_p_insert(char *arg, char *path)
{
	t_ht	*entry;

	entry = NULL;
	if (path)
	{
		entry = (t_ht*)ft_memalloc(sizeof(t_ht));
		entry->key = ft_strdup(arg);
		entry->value = ft_strdup(path);
		entry->hits = 0;
		entry->next = NULL;
	}
	return (entry);
}

void		del_hash(t_hash **h_table, char **args)
{
	t_hash	*hashtable;
	t_ht	*current;
	int		i;
	int		slot;

	hashtable = *h_table;
	i = 1;
	while (args[++i])
	{
		slot = hash_function(args[i]);
		current = hashtable->list[slot];
		if (delete_list(current, &(hashtable->list[slot]), args[i]) == 0)
		{
			ft_putstr_fd("42sh: hash: ", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd(": not found", 2);
		}
	}
}

int			delete_list(t_ht *list, t_ht **main_head, char *arg)
{
	t_ht	*current;
	t_ht	*prev;

	current = list;
	prev = NULL;
	if (current)
	{
		if (ft_strcmp(arg, current->key) == 0)
		{
			list = current->next;
			*main_head = list;
			return (free_node(&current));
		}
		while (current && (ft_strcmp(arg, current->key) != 0))
		{
			prev = current;
			current = current->next;
		}
		if (current == NULL)
			return (0);
		prev->next = current->next;
		return (free_node(&current));
	}
	else
		return (0);
}

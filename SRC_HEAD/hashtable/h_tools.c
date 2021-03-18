/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_tools.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 02:23:39 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/18 12:16:53 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		l_flag_mini(char *str, t_ht *current)
{
	while (current)
	{
		if (ft_strcmp(str, current->key) == 0)
			break ;
		current = current->next;
	}
	if (!current)
		l_flag_error(str);
}

void		l_flag_valid(t_hash *hashtable, int slot)
{
	int		c;
	int		i;
	t_ht	*current;

	c = 0;
	i = -1;
	while (++i < TABLE_SIZE && slot == -1)
	{
		current = hashtable->list[i];
		while (current)
		{
			l_flag_print(current->value, current->key);
			c++;
			current = current->next;
		}
	}
	if (!c && slot == -1)
		ft_putendl_fd("42sh: hash table empty", 2);
}

void		p_flag_mini(char **args, t_hash **h_table)
{
	int		i;
	int		slot;
	t_ht	*current;
	t_hash	*hashtable;

	i = 2;
	hashtable = *h_table;
	if (!args[3])
		return (aff_hashtable(h_table));
	while (args[++i])
	{
		slot = hash_function(args[i]);
		current = hashtable->list[slot];
		if (!current)
			hashtable->list[slot] = hash_p_insert(args[i], args[2]);
		else
			p_flag_free(&(hashtable->list[slot]), args[i], args[2]);
	}
}

void		p_flag_free(t_ht **h_list, char *str, char *path)
{
	t_ht	*current;

	current = *h_list;
	while (current)
	{
		if (ft_strcmp(str, current->key) == 0)
		{
			ft_strdel(&current->value);
			current->value = ft_strdup(path);
			current->hits = 0;
		}
		current = current->next;
	}
}

int			free_node(t_ht **list)
{
	t_ht	*current;

	current = *list;
	ft_strdel(&current->key);
	ft_strdel(&current->value);
	free(current);
	return (1);
}

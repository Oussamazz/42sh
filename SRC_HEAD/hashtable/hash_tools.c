/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 18:36:01 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/18 12:16:56 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		reset_hits(char **args, t_hash **h_table)
{
	t_hash		*hashtable;
	t_ht		*current;
	int			i;
	int			slot;

	hashtable = *h_table;
	i = 1;
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
				current->hits = 0;
				break ;
			}
			current = current->next;
		}
	}
}

void		delete_hashtable(t_hash **h_table, int len)
{
	int		i;

	i = 0;
	while (i < TABLE_SIZE)
	{
		if ((*h_table)->list[i])
			(*h_table)->list[i] = del_list(&(*h_table)->list[i], len);
		i++;
	}
}

void		aff_hashtable(t_hash **h_table)
{
	t_hash	*hashtable;
	t_ht	*current;
	int		i;
	int		c;

	hashtable = *h_table;
	i = -1;
	c = 0;
	while (++i < TABLE_SIZE)
	{
		current = hashtable->list[i];
		while (current)
		{
			if (!c)
				ft_putendl_fd("hits    command", 1);
			ft_putstr_fd("   ", 1);
			ft_putnbr_fd(current->hits, 1);
			ft_putstr_fd("    ", 1);
			ft_putendl_fd(current->value, 1);
			c++;
			current = current->next;
		}
	}
	if (!c)
		ft_putendl_fd("42sh: hash table empty", 2);
}

t_ht		*del_list(t_ht **list, int len)
{
	t_ht		*current;
	t_ht		*head;
	t_ht		*next;

	current = *list;
	if (current && current->hits != 0 && len > 2)
	{
		next = current->next;
		free_node(&current);
		current = next;
	}
	else if (len == 2)
	{
		next = current->next;
		free_node(&current);
		current = next;
	}
	head = current;
	del_list_mini(&current, len);
	return (head);
}

int			hash_function(char *str)
{
	int		i;
	int		p;
	int		p_pow;
	int		hash_value;

	i = -1;
	hash_value = 0;
	p_pow = 1;
	p = 31;
	while (str[++i])
	{
		hash_value = (hash_value + (str[i] - 'a' + 1) * p_pow) % TABLE_SIZE;
		p_pow = (p_pow * p) % TABLE_SIZE;
	}
	if (hash_value < 0)
		hash_value = hash_value * (-1);
	return (hash_value);
}

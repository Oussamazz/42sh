/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 02:15:49 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/18 12:16:47 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		l_flag(t_hash **h_table, char **args)
{
	t_hash	*hashtable;
	t_ht	*current;
	int		c;
	int		slot;

	hashtable = *h_table;
	c = 1;
	slot = -1;
	while (args[++c])
	{
		slot = hash_function(args[c]);
		current = hashtable->list[slot];
		l_flag_mini(args[c], current);
	}
	l_flag_valid(hashtable, slot);
}

void		d_flag(t_hash **h_table, char **args)
{
	int		len;

	len = ft_argslen(args);
	if (len > 2)
		del_hash(h_table, args);
	else if (len == 2)
		aff_hashtable(h_table);
}

void		t_flag(t_hash **h_table, char **args)
{
	int		len;

	len = ft_argslen(args);
	if (len > 2)
		search_hash(h_table, args, len);
	else
		ft_putendl_fd("42sh: hash: -t: option requires an argument", 2);
}

void		p_flag(t_hash **h_table, char **args)
{
	if (ft_argslen(args) == 2)
		ft_hash_error(NULL);
	else
		p_flag_mini(args, h_table);
}

void		search_hash(t_hash **h_table, char **args, int len)
{
	t_hash	*hashtable;
	t_ht	*current;
	int		slot;

	hashtable = *h_table;
	if (len == 3)
	{
		slot = hash_function(args[2]);
		current = hashtable->list[slot];
		if (!current)
			l_flag_error(args[2]);
		while (current)
		{
			if (ft_strcmp(args[2], current->key) == 0)
			{
				ft_putendl_fd(current->value, 1);
				break ;
			}
			current = current->next;
		}
	}
	else
		search_hash_mini(h_table, args);
}

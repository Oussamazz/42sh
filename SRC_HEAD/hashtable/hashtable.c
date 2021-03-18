/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 17:57:11 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/18 12:17:05 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_ht	*ht_insert(char *str, char **tabs, char **print)
{
	t_ht	*entry;
	char	*path;

	path = valid_path(str, tabs, print);
	entry = NULL;
	if (path)
	{
		entry = (t_ht*)ft_memalloc(sizeof(t_ht));
		entry->key = ft_strdup(str);
		entry->value = ft_strdup(path);
		free(path);
		entry->hits = 1;
		entry->next = NULL;
	}
	return (entry);
}

char	*ft_hashtable(char **args, char **tabs, t_hash **h_table, char **print)
{
	unsigned	int	slot;
	t_ht			*current;
	char			*ret;
	t_hash			*hashtable;

	hashtable = *h_table;
	slot = hash_function(args[0]);
	current = hashtable->list[slot];
	if (current == NULL)
	{
		if (args[0][0] == '.' || args[0][0] == '/')
		{
			if (ft_hash_complete(print, args))
				return (ft_strdup(args[0]));
			return (NULL);
		}
		hashtable->list[slot] = ht_insert(args[0], tabs, print);
		if (hashtable->list[slot])
			return (ft_strdup(hashtable->list[slot]->value));
		return (NULL);
	}
	if ((ret = ft_hash_complete_s(hashtable, args, tabs, print)))
		return (ret);
	return (ret);
}

char	*ft_hash_complete_s(t_hash *hashtable, char **args, char **tabs,
							char **print)
{
	t_ht	*current;
	t_ht	*prev;
	int		slot;

	slot = hash_function(args[0]);
	current = hashtable->list[slot];
	while (current)
	{
		if (ft_strcmp(current->key, args[0]) == 0 &&
			++hashtable->list[slot]->hits)
			return (ft_strdup(hashtable->list[slot]->value));
		prev = current;
		current = current->next;
	}
	prev->next = ht_insert(args[0], tabs, print);
	return (ft_strdup(hashtable->list[slot]->value));
}

int		ft_hash_complete(char **print, char **args)
{
	DIR		*dir;

	if (access(args[0], F_OK) == 0)
	{
		if ((access(args[0], X_OK) == 0) && ((dir = opendir(args[0])) == NULL))
			return (1);
		else
			*print = ft_strjoin("42sh : permission denied: ", args[0]);
	}
	else
		*print = ft_strjoin("42sh : command not found: ", args[0]);
	return (0);
}

void	ft_hash(char **args, t_hash **h_table)
{
	int			len;

	len = ft_argslen(args);
	if (len > 1)
	{
		if (ft_strcmp(args[1], "-r") == 0)
		{
			reset_hits(args, h_table);
			delete_hashtable(h_table, len);
		}
		else if (ft_strcmp(args[1], "-l") == 0)
			l_flag(h_table, args);
		else if (ft_strcmp(args[1], "-d") == 0)
			d_flag(h_table, args);
		else if (ft_strcmp(args[1], "-t") == 0)
			t_flag(h_table, args);
		else if (ft_strcmp(args[1], "-p") == 0)
			p_flag(h_table, args);
		else if (args[1][0] == '-')
			ft_hash_error(args[1]);
	}
	else
		aff_hashtable(h_table);
}

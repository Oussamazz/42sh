/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_hash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:33:17 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/29 16:33:19 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_hash			*alloc_hash(t_hash **h_table)
{
	int		i;
	t_hash	*save_hash;

	i = 0;
	save_hash = ht_create();
	while (i < TABLE_SIZE)
	{
		if ((*h_table)->list[i])
			save_hash->list[i] = alloc_list((*h_table)->list[i]);
		i++;
	}
	return (save_hash);
}

t_ht			*alloc_list(t_ht *list)
{
	t_ht	*head;
	t_ht	*addr;
	int		c;

	head = NULL;
	addr = NULL;
	c = 0;
	while (list)
	{
		head = (t_ht*)ft_memalloc(sizeof(t_ht));
		if (c == 0 && head)
			addr = head;
		head->value = ft_strdup(list->value);
		head->key = ft_strdup(list->key);
		head->hits = list->hits;
		list = list->next;
		head = head->next;
		c++;
	}
	return (addr);
}

static	char	*find_path(char **tabs)
{
	int i;

	i = 0;
	while (tabs[i])
	{
		if (ft_strncmp(tabs[i], "PATH=", 5) == 0)
			return (tabs[i]);
		i++;
	}
	return (NULL);
}

char			*valid_path(char *cmd_name, char **tabs, char **print)
{
	char	*p;
	char	*str;
	char	**path;
	int		i;

	i = -1;
	p = NULL;
	if (!(p = find_path(tabs)) || !tabs)
		return (NULL);
	path = ft_strsplit(&p[5], ':');
	while (path[++i])
	{
		str = absolute_path(path[i], cmd_name);
		if (access(str, F_OK) == 0)
		{
			if (access(str, X_OK) != 0)
				print[0] = ft_strjoin("42sh : permission denied: ", str);
			ft_free_arr(path);
			return (str);
		}
		ft_strdel(&str);
	}
	print[0] = ft_strjoin("42sh : command not found: ", cmd_name);
	ft_free_arr(path);
	return (NULL);
}

t_hash			*ht_create(void)
{
	t_hash		*hashtable;
	int			i;

	if (!(hashtable = (t_hash*)ft_memalloc(sizeof(t_hash))))
		return (NULL);
	if (!(hashtable->list = (t_ht**)ft_memalloc(sizeof(t_ht*) * TABLE_SIZE)))
		return (NULL);
	i = -1;
	while (++i < TABLE_SIZE)
		hashtable->list[i] = NULL;
	return (hashtable);
}

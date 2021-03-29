/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_alias_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:22:55 by afaragi           #+#    #+#             */
/*   Updated: 2021/03/29 16:21:48 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char		*ft_strdup_from_to(const char *s, int start, int end)
{
	int		c;
	char	*d;
	char	*rzlt;

	if (!s)
		return (NULL);
	c = 0;
	if (!(d = (char *)malloc(sizeof(char) * ((end - start) + 1))))
		return (NULL);
	while (start < end)
	{
		d[c++] = s[start++];
	}
	d[c] = '\0';
	rzlt = ft_strdup(d);
	free(d);
	if (rzlt && !rzlt[0])
		ft_strdel(&rzlt);
	return (rzlt);
}

t_alias		*check_alias_repeate(char *name, t_alias *alias)
{
	if (alias)
	{
		while (alias)
		{
			if (!(ft_strcmp(alias->name, name)))
				return (alias);
			alias = alias->next;
		}
	}
	return (NULL);
}

void		del(void *s, void *str)
{
	ft_strdel((void *)&s);
	ft_strdel((void *)&str);
}

void		ft_one_alias_del(t_alias **alst, void (*del)(void *, void *))
{
	if (alst)
	{
		del((*alst)->name, (*alst)->value);
		ft_memdel((void **)alst);
	}
}

void		free_alias_list(t_alias **alst, void (*del)(void *, void *))
{
	t_alias	*li;

	if (alst)
	{
		while (*alst)
		{
			li = (*alst)->next;
			ft_one_alias_del(&(*alst), del);
			*alst = li;
		}
	}
}

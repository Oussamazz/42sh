/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 18:26:15 by ahmcherk          #+#    #+#             */
/*   Updated: 2021/03/29 15:44:00 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_envv		*ft_setnewnode(void)
{
	t_envv		*new;

	if (!(new = (t_envv *)malloc(sizeof(t_envv))))
		return (NULL);
	new->name = NULL;
	new->content = NULL;
	new->all = NULL;
	new->type = 0;
	new->next = NULL;
	return (new);
}

void		ft_setaddnode(char *name, char *content, char *all, int type)
{
	t_envv	*head;

	head = NULL;
	if (!g_set)
	{
		if (!(g_set = ft_setnewnode()))
			return ;
		g_set->name = ft_strdup(name);
		g_set->content = ft_strdup(content);
		g_set->all = ft_strdup(all);
		g_set->type = type;
		return ;
	}
	head = g_set;
	while (g_set->next)
		g_set = g_set->next;
	if (!(g_set->next = ft_setnewnode()))
		return ;
	g_set->next->name = ft_strdup(name);
	g_set->next->content = ft_strdup(content);
	g_set->next->all = ft_strdup(all);
	g_set->next->type = type;
	g_set = head;
}

void		ft_setdelnode(t_envv **node, t_envv **prev, int count)
{
	t_envv	*tmp;

	tmp = NULL;
	if (count == 1)
		tmp = (*node)->next;
	else
		(*prev)->next = (*node)->next;
	ft_strdel(&(*node)->name);
	ft_strdel(&(*node)->content);
	ft_strdel(&(*node)->all);
	free(*node);
	*node = NULL;
	if (count == 1)
		g_set = tmp;
}

void		ft_listtotab(void)
{
	int		i;
	int		j;
	t_envv	*head;

	i = -1;
	j = -1;
	if (g_envtab)
		ft_memdel((void**)&g_envtab);
	if (g_settab)
		ft_strdbldel(&g_settab);
	if (!(g_envtab = (char **)malloc(sizeof(char *) * 400)) ||
		!(g_settab = (char **)malloc(sizeof(char *) * 400)))
		return ;
	head = g_set;
	while (g_set)
	{
		g_settab[++i] = ft_strdup(g_set->all);
		if (g_set->type == IN_ENV)
			g_envtab[++j] = g_settab[i];
		g_set = g_set->next;
	}
	g_settab[++i] = NULL;
	g_envtab[++j] = NULL;
	g_set = head;
}

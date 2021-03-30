/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 16:41:49 by ahmcherk          #+#    #+#             */
/*   Updated: 2021/03/30 10:33:19 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_envvinit(char **env)
{
	int		i;
	int		j;
	char	*name;

	i = -1;
	j = 0;
	name = NULL;
	g_set = NULL;
	g_envtab = NULL;
	g_settab = NULL;
	while (env[++i])
	{
		j = -1;
		while (env[i][++j] && env[i][j] != '=')
			;
		name = ft_strsub(env[i], 0, j);
		ft_setaddnode(name, ft_strchr(env[i], '=') + 1, env[i], IN_ENV);
		ft_strdel(&name);
	}
}

void	ft_tabfree(void)
{
	free(g_envtab);
	g_envtab = NULL;
	ft_strdbldel(&g_settab);
}

void	ft_listfree(void)
{
	while (g_set)
		ft_setdelnode(&g_set, NULL, 1);
}

void	ft_export(char **ta)
{
	t_envv	*var;
	int		i;

	var = NULL;
	i = 0;
	while (ta[++i])
	{
		var = ft_varchr(ta[i], SEARCH);
		var->type = IN_ENV;
	}
}

void	ft_envcpy(t_env **head)
{
	t_env	*tmp;
	t_envv	*head_set;

	tmp = NULL;
	head_set = g_set;
	free_env_list(head);
	while (g_set)
	{
		if (g_set->type == IN_ENV)
			addtolist(head, ft_strdup(g_set->name), ft_strdup(g_set->content));
		g_set = g_set->next;
	}
	g_set = head_set;
}

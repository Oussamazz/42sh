/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macos <macos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 16:41:49 by ahmcherk          #+#    #+#             */
/*   Updated: 2021/03/21 21:07:36 by macos            ###   ########.fr       */
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
		// ft_putendl(g_set->name);
		ft_strdel(&name);
	}
}

void	ft_tabfree(void)
{
	free(g_envtab);
	g_envtab = NULL;
	ft_strdbldel(&g_settab);
}

void	ft_listfree(void) // free all the list
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

int		ft_tmpvarcheck(t_lexer *tokenz)
{
	t_lexer		*node;
	int			old_type;

	node = tokenz;
	old_type = 0;
	while (node)
	{
		if (node->type != ENV && old_type == ENV)
			return (1);
		old_type = tokenz->type;
		node = node->next;
	}
	return (0);
}

void	ft_addtmpvar(t_env **head, char *data)
{
	char	*name;
	int		i;

	name = NULL;
	i = -1;
	while (data[++i] && data[i] != '=')
		;
	name = ft_strsub(data, 0, i);
	if (env_exist(head, name) == 0)
		addtolist(head, ft_strdup(name), ft_strdup(ft_strchr(data, '=') + 1));
	else
		modify_env(head, ft_strdup(name), ft_strdup(ft_strchr(data, '=')));
	ft_strdel(&name);
}

void	ft_execenv(t_env **head, t_lexer *tokenz)
{
	t_env	*tmp;
	int		tmp_check;
	t_lexer	*head_lexer;

	ft_putendl("dkhlt l execenv");
	tmp = *head;
	head_lexer = tokenz;
	tmp_check = ft_tmpvarcheck(tokenz);
	while (tokenz && tokenz->type == ENV)
	{
		if (tmp_check)
			ft_addtmpvar(head, tokenz->data);
		else
			ft_newvar(tokenz->data, NOT_IN_ENV);
		tokenz = tokenz->next;
	}
	ft_listtotab();
}

// int		main(int argc, char **argv, char **env)
// {
// 	t_envv	*head;
// 	g_envtab = NULL;
// 	g_settab = NULL;
// 	g_set = NULL;
// 	ft_envvinit(env); // extract the env table to the t_envv list
// 	head = g_set;
// 	// while (g_set) // print for test
// 	// {
// 	// 	ft_putnbr(g_set->type);
// 	// 	ft_putstr(g_set->name);
// 	// 	ft_putstr("=");
// 	// 	ft_putendl(g_set->content);
// 	// 	g_set = g_set->next;
// 	// }
// 	ft_newvar("TERM_PROGRAM", NOT_IN_ENV);
// 	// ft_varchr("toto", DEL);
// 	ft_listtotab();
// 	ft_putdblstr(g_settab);
// 	ft_listfree();
// 	ft_tabfree();
// 	// g_set = head;
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value_exp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macos <macos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 19:04:25 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/21 21:15:11 by macos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char		*get_value_expansion(char *env_name, t_env **head)
{
	char	*env_value;
	t_envv	*curr;

	curr = NULL;
	env_value = NULL;
	if (g_set)
		curr = g_set;
	if (env_name && curr)
	{
		// puts("dkhlt l expansion");
		while (curr)
		{
			if (ft_strequ(curr->name, env_name))
				return ((env_value = ft_strdup(curr->content)));
			curr = curr->next;
		}
	}
	return (env_value);
}

char		*get_value_expansion_cd(char *env_name, t_env **head)
{
	char	*env_value;
	t_env	*curr;

	curr = NULL;
	env_value = NULL;
	if (head)
		curr = *head;
	if (env_name && curr)
	{
		// puts("dkhlt l expansion");
		while (curr)
		{
			if (ft_strequ(curr->env_var_name, env_name))
				return ((env_value = ft_strdup(curr->env_var_value)));
			curr = curr->next;
		}
	}
	return (env_value);
}


char		*get_value_expansion_path(char *env_name)
{
	char	*env_value;
	t_envv	*curr;

	curr = NULL;
	env_value = NULL;
	if (g_set)
		curr = g_set;
	if (env_name && curr)
	{
		while (curr)
		{
			if (ft_strequ(curr->name, env_name))
				return ((env_value = ft_strdup(curr->content)));
			curr = curr->next;
		}
	}
	return (env_value);
}

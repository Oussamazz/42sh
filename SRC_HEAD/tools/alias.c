/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 17:11:21 by afaragi           #+#    #+#             */
/*   Updated: 2021/03/29 16:17:31 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	free2dm(char ***str)
{
	int i;

	i = 0;
	while ((*str)[i])
	{
		ft_strdel(&(*str)[i]);
		i++;
	}
	free((*str));
}

void	clean_vars(t_a_v *vars, int flag)
{
	ft_strdel(&(*vars).endline);
	ft_strdel(&(*vars).startline);
	ft_strdel(&(*vars).value);
	if (flag)
		ft_strdel(&(*vars).tmp);
}

char	*return_value(char *name, t_alias *alias)
{
	if (alias)
	{
		while (alias)
		{
			if (!ft_strcmp(alias->name, name))
				return (ft_strdup(alias->value));
			alias = alias->next;
		}
	}
	return (NULL);
}

void	ft_move_replace(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		str[i] = str[i + 1];
}

int		is_indice(int c)
{
	if (c == ' ' || c == '\n' || c == ';' || c == '|' || c == '&')
		return (1);
	return (0);
}

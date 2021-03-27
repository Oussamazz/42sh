/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:06:47 by ahmcherk          #+#    #+#             */
/*   Updated: 2021/03/27 14:36:54 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void		ft_newvar(char *str, int type)
{
	char	*name;
	int		i;
	t_envv	*node;

	i = -1;
	name = NULL;
	node = NULL;
	if (!str)
		return ;
	while (str[++i] && str[i] != '=')
		;
	if (i == (int)ft_strlen(str))
		return ;
	name = ft_strsub(str, 0, i);
	if ((node = ft_varchr(name, SEARCH)))
		ft_modvar(&node, str);
	else
		ft_setaddnode(name, ft_strchr(str, '=') + 1, str, type);
	ft_strdel(&name);
}

void		ft_modvar(t_envv **node, char *str)
{
	ft_strdel(&(*node)->all);
	ft_strdel(&(*node)->content);
	(*node)->all = ft_strdup(str);
	(*node)->content = ft_strdup(ft_strchr(str, '=') + 1);
}

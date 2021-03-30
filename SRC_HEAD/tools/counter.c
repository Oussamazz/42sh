/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:27:29 by afaragi           #+#    #+#             */
/*   Updated: 2021/03/30 11:10:14 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			counter(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
			i++;
	}
	return (i);
}

t_alias		*copy_list(t_alias *alias)
{
	t_alias	*cpy;
	t_alias	*new;

	new = NULL;
	cpy = NULL;
	if (alias)
	{
		while (alias)
		{
			new = alias_create(alias->name, alias->value);
			cpy = alias_lst_adder(&cpy, new);
			alias = alias->next;
		}
	}
	return (cpy);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vartools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmcherk <ahmcherk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 15:24:07 by ahmcherk          #+#    #+#             */
/*   Updated: 2021/03/17 17:07:58 by ahmcherk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_envv		*ft_varchr(char *str, int flag)
{
	t_envv	*head;
	t_envv	*ret;
	t_envv	*prev;
	int		count;

	head = g_set;
	ret = NULL;
	count = 0;
	prev = NULL;
	while (g_set)
	{
		count++;
		if (!ft_strcmp(str, g_set->name))
		{
			if (flag == DELL)
				ft_setdelnode(&g_set, &prev, count);
			ret = g_set;
			break ;
		}
		prev = g_set;
		g_set = g_set->next;
	}
	if (count != 1)
		g_set = head;
	return (ret);
}

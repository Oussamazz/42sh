/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_fc_l.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <yabakhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 17:27:33 by yabakhar          #+#    #+#             */
/*   Updated: 2021/03/29 17:28:04 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int			ft_abs(int num)
{
	return (num = (num >= 0) ? num : (num * -1));
}

void		get_index_in_list(t_node **history, int debut)
{
	int		i;

	i = 0;
	while (*history)
	{
		if (i == debut)
			return ;
		(*history) = (*history)->next;
		i++;
	}
	return ;
}

char		*get_content_in_list(int debut)
{
	int		i;
	t_node	*history;

	i = 0;
	history = add_to_history(NULL);
	while (history)
	{
		if (i == debut)
			return (history->content);
		(history) = (history)->next;
		i++;
	}
	return (NULL);
}

int			calc_list(t_node *history)
{
	int		i;

	i = 0;
	while (history)
	{
		i++;
		history = history->next;
	}
	return (i);
}

int			ft_sin(int i)
{
	if (i >= 0)
		return (-1);
	return (1);
}

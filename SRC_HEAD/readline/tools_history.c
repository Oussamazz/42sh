/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <yabakhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 17:42:36 by yabakhar          #+#    #+#             */
/*   Updated: 2021/03/29 17:44:43 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void		ft_rev_list(t_node **history)
{
	while ((*history))
	{
		if ((*history)->next == NULL)
			break ;
		(*history) = (*history)->next;
	}
}

void		print_in_history(const char *file)
{
	int		fd;
	t_node	*new;

	new = add_to_history(NULL);
	ft_rev_list(&(new));
	if ((fd = open(file, O_RDWR | O_TRUNC | O_CREAT, 00600)) == -1)
		return ;
	while (new)
	{
		ft_putendl_fd(new->content, fd);
		new = new->prev;
	}
	close(fd);
}

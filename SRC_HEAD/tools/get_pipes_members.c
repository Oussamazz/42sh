/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipes_members.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 12:39:43 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/29 16:27:38 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	get_size(t_miniast *lst)
{
	int		count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->pipe;
	}
	return (count);
}

char		**get_pipes_members(t_miniast *lst)
{
	int		i;
	char	**arr;
	int		size;

	arr = NULL;
	size = get_size(lst);
	if (lst)
	{
		if (!(arr = ft_memalloc(sizeof(char *) * (size + 1))))
			return (NULL);
		i = 0;
		while (lst)
		{
			arr[i++] = ft_strdup(lst->cmd[0]);
			lst = lst->pipe;
		}
		arr[i] = NULL;
		print_arr(arr);
	}
	return (arr);
}

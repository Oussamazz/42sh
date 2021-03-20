/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 18:48:56 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/17 12:40:24 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		ft_free_arr(char **arr)
{
	int		i;

	if (arr)
	{
		i = 0;
		while (arr[i] != NULL)
		{
			ft_strdel(&arr[i]);
			i++;
		}
		if (arr)
			free(arr);
		arr = NULL;
	}
}

void		free_env_list(t_env **head)
{
	t_env	*tmp;

	tmp = NULL;
	while (*head)
	{
		tmp = (*head)->next;
		ft_strdel(&(*head)->env_var_name);
		ft_strdel(&(*head)->env_var_value);
		free(*head);
		*head = tmp;
	}
	*head = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_job_members.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 15:16:06 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/29 16:12:51 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

size_t		get_len(t_miniast *tree)
{
	size_t	len;

	len = 0;
	while (tree)
	{
		len++;
		tree = tree->pipe;
	}
	return (len);
}

char		**get_job_members(t_miniast *tree)
{
	int		i;
	char	**arr;
	size_t	len;
	bool	flag;

	flag = 0;
	arr = NULL;
	len = get_len(tree);
	if (!(arr = (char **)ft_memalloc(sizeof(char *) * (len + 2))))
		return (NULL);
	i = 0;
	while (tree && tree->cmd)
	{
		if (tree->pipe)
			flag = 1;
		if (!(arr[i++] = ft_strjoin_cmds(tree->cmd, flag)))
			return (NULL);
		flag = 0;
		tree = tree->pipe;
	}
	arr[i] = ft_strdup(" &");
	arr[i + 1] = NULL;
	return (arr);
}

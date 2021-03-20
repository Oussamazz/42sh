/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbl_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmcherk <ahmcherk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 12:17:28 by ahmcherk          #+#    #+#             */
/*   Updated: 2021/03/17 15:41:32 by ahmcherk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int		ft_dblstrlen(char **str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**ft_strdbldup(char **str)
{
	int		i;
	char	**dup;

	if (!str)
		return (NULL);
	i = 0;
	if (!(dup = (char **)malloc(sizeof(char *) * (ft_dblstrlen(str) + 1))))
		return (NULL);
	while (str[i])
	{
		dup[i] = ft_strdup(str[i]);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

void	ft_strdbldel(char ***str)
{
	int i;

	i = -1;
	if (!(*str))
		return ;
	while ((*str)[++i])
		ft_strdel(&(*str)[i]);
	ft_strdel(&(*str)[i]);
	free(*str);
	*str = NULL;
}

void	ft_putdblstr(char **str)
{
	int		i;

	i = -1;
	if (!str)
		return ;
	while (str[++i])
		ft_putendl(str[i]);
}

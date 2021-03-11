/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrtostr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 12:52:08 by oelazzou          #+#    #+#             */
/*   Updated: 2021/02/24 12:56:26 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_arrtostr(char **arr)
{
	int 	i;
	size_t	size;
	char	*str;
	char *tmp;

	str = NULL;
	if (arr)
	{
		i = 0;
		str = ft_strdup("");
		while (arr[i])
		{
			tmp = str;
			if (!(str = ft_strjoin(str, arr[i++])))
				return (NULL);
			ft_strdel(&tmp);
		}
	}
	return (str);
}
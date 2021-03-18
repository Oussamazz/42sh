/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 02:38:24 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/18 19:11:18 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char			*get_content_quote(char *buffer, char c,
	t_pointt *coord, int flag)
{
	const char	*tmp;
	char 		*ptr;
	int 		i;
	char		*str;

	tmp = buffer;
	if (buffer)
	{
		while (*buffer != c)
			buffer++;
		str = ft_strsub(tmp, 0, buffer - tmp);
		if (!flag)
			flag = is_blank(buffer[1]) ? 0 : 1;
		coord->no_space = flag;
		return (str);
	}
	return (NULL);
}
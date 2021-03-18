/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 02:38:24 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/18 18:38:27 by afaragi          ###   ########.fr       */
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
		{
			if(*buffer == '\\' && (*(buffer + 1) && (*(buffer + 1) == '\'' || *(buffer + 1) =='\"')))       ////////biggy
			{
				ptr = buffer;
				i = -1;
				while(ptr[i++])
					ptr[i] = ptr[i + 1]; 
				buffer += 2;
				continue;
			}
			buffer++;
		}
		str = ft_strsub(tmp, 0, buffer - tmp);
		if (!flag)
			flag = is_blank(buffer[1]) ? 0 : 1;
		coord->no_space = flag;
		return (str);
	}
	return (NULL);
}
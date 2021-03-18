/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 19:11:38 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/18 18:31:04 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int		word_count(char *s)
{
	int			i;
	int flag = 0;
	int			res;

	i = 0;
	res = 0;
	while (s[i] != '\0' && s[i + 1])
	{
		if (!is_blank(s[i]) && is_blank(s[i + 1]))
			res++;
		if(s[i] == '\\' && flag)
		{
			flag = 0;
		}
		else if(s[i] == '\\' )
		{
			flag = 1;
		}
		if (i && (s[i] == '$' ||s[i] == '\\')  && !flag)
			res++;
		else if (is_blank(s[i]))
		{
			while (is_blank(s[i]))
				i++;
			continue ;
		}
		i++;
	}
	if ((!s[i] && ft_isascii(s[i - 1])) || (!s[i + 1] && ft_isascii(s[i])))
		res++;
	return (res);
}

static int		get_type(char c)
{
	if (is_blank(c))
		return (1);
	if (!is_blank(c))
		return (2);
	return (2);
}


static int		word_len(char *s)
{
	int			len;
	int			type;
	int index = 0;

	len = 0;
	type = get_type(*s);
	
	while (*s != '\0')
	{
		if(*s == '\\' && len && *(s - 1) != '\\' )
			index = 0;
		else if(*s == '\\')
			index = 1;
		if (len && (*s == '$' || *s == '\\' )&& !index)   ///////bigggy
			break ;
		if (len && ft_isalnum(*s) && index)   ///////bigggy
			index = 0;
		if (get_type(*s) == type)
			len++;
		else if (len && (!ft_isalnum(*s)))
			break ;
		else
			break ;
		s++;
	}
	return (len);
}

char			**strsplit(char const *s, int flag)
{
	int			word_countx;
	char		**str;
	int			i;
	

	if (!s)
		return (NULL);
	word_countx = (word_count((char *)s) * 2);
	str = (char **)ft_memalloc(sizeof(char *) * (word_countx + 1));
	i = 0;
	if (!str)
		return (NULL);
	while (word_countx-- && *s)
	{
		if (!(str[i] = ft_strsub(s, 0, word_len((char *)s))))
			return (NULL);
		s = s + word_len((char *)s);
		i++;
	}
	str[i] = 0;
	return (str);
}

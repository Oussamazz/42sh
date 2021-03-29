/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 19:11:38 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/29 17:55:19 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int		word_count(char *s)
{
	t_wc			wc;

	ft_bzero(&wc, sizeof(t_wc));
	while (s[wc.i] != '\0' && s[wc.i + 1])
	{
		if (!is_blank(s[wc.i]) && is_blank(s[wc.i + 1]))
			wc.res++;
		if (s[wc.i] == '\\' && wc.flag)
			wc.flag = 0;
		else if (s[wc.i] == '\\')
			wc.flag = 1;
		if (wc.i && (s[wc.i] == '$' || s[wc.i] == '\\') && !wc.flag)
			wc.res++;
		else if (is_blank(s[wc.i]))
		{
			while (is_blank(s[wc.i]))
				wc.i++;
			continue ;
		}
		wc.i++;
	}
	if ((!s[wc.i] && ft_isascii(s[wc.i - 1]))
	|| (!s[wc.i + 1] && ft_isascii(s[wc.i])))
		wc.res++;
	return (wc.res);
}

static	int		get_type(char c)
{
	if (is_blank(c))
		return (1);
	if (!is_blank(c))
		return (2);
	return (2);
}

static int		word_len(char *s)
{
	t_wlen			wl;

	wl.len = 0;
	wl.type = get_type(*s);
	wl.index = 0;
	while (*s != '\0')
	{
		if (*s == '\\' && wl.len && *(s - 1) != '\\')
			wl.index = 0;
		else if (*s == '\\')
			wl.index = 1;
		if (wl.len && (*s == '$' || *s == '\\') && !wl.index)
			break ;
		if (wl.len && ft_isalnum(*s) && wl.index)
			wl.index = 0;
		if (get_type(*s) == wl.type)
			wl.len++;
		else if (wl.len && (!ft_isalnum(*s)))
			break ;
		else
			break ;
		s++;
	}
	return (wl.len);
}

char			**strsplit(char const *s)
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

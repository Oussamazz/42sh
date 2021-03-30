/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_comletion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <yabakhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 17:19:54 by yabakhar          #+#    #+#             */
/*   Updated: 2021/03/29 17:20:51 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int			is_in_str(char c, const char *cmp)
{
	while (*cmp)
	{
		if (*cmp == c)
			return (1);
		cmp++;
	}
	return (0);
}

char		*ft_strrsearch(char *s, const char *cmp, size_t size)
{
	while (size > 0)
	{
		if (is_in_str(s[size], cmp))
			return (s + size);
		size--;
	}
	return (s + size);
}

char		*ft_strrsearch2(char *s, const char *cmp, size_t size)
{
	while (size > 0)
	{
		if (!is_in_str(s[size], cmp))
			return (s + size);
		size--;
	}
	return (s + size);
}

void		get_str_for_search(char *str, t_line *line, int cursor_pos)
{
	int		tmp;
	int		len;
	int		debut;

	tmp = line->compl.prefix_pos;
	len = cursor_pos - tmp;
	debut = (tmp > 0) ? tmp : tmp++;
	line->compl.str = ft_strsub(str, debut, len);
}

void		ft_affiche_brackets(char *content, t_line *line)
{
	if (line->compl.type == 1)
		ft_putchar('$');
	if (line->compl.bracket)
		ft_putchar('{');
	ft_putstr(content);
	if (line->compl.bracket)
		ft_putchar('}');
}

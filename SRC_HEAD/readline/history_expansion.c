/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <yabakhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 20:16:12 by yabakhar          #+#    #+#             */
/*   Updated: 2021/03/29 17:35:04 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

char		*ft_get_all_node(char *next_char, char *str)
{
	char	*last_histroy;
	char	*rest_value;
	int		i;

	i = 0;
	if (!(ft_strncmp(next_char, "!", 1)))
	{
		while (str[i] == '!')
			i++;
		rest_value = ft_strsub(next_char, i - 1, ft_strlen(str) - i);
		if ((i % 2) == 0)
		{
			i = i / 2;
			last_histroy = get_all_value(i);
			last_histroy = ft_freejoin(last_histroy, rest_value, 2);
			return (last_histroy);
		}
		else
			return (ft_is_not_pair(i, rest_value));
	}
	return (NULL);
}

char		*ft_make_value_expansion(char *next_char, char *str)
{
	char	*return_value;

	return_value = ft_get_all_node(next_char, str);
	if (return_value != NULL)
		return (return_value);
	else if (ft_isnumber(next_char) || ((next_char[0] == '-') &&
		(ft_isnumber(next_char + 1))))
	{
		if ((next_char[0] == '-') && (next_char[1] == '\0'))
		{
			ft_putendl("bash: !: event not found");
			return (0);
		}
		return (get_node(next_char));
	}
	else
		return (NULL);
}

char		*ft_get_value(char *str, int debut, int fin)
{
	int		i;
	int		len;
	char	*rest;
	char	*tmp;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (i >= debut)
			len++;
		if (i == fin)
			break ;
		i++;
	}
	rest = ft_strsub(str, debut, len);
	tmp = ft_make_value_expansion(rest + 1, rest);
	ft_strdel(&rest);
	return (tmp);
}

int			handel_history_expansion(char *str, t_expansion_h *expansion)
{
	if (str[expansion->i] != '!')
	{
		while (str[expansion->i] && str[expansion->i] != '!')
			expansion->i++;
		expansion->tmp = ft_get_value(str, expansion->j, expansion->i - 1);
		if (expansion->tmp)
		{
			if (expansion->j == 0)
				expansion->hold = ft_freejoin(expansion->tmp,
					expansion->hold, 2);
			else
				expansion->hold = ft_freejoin(expansion->hold,
					expansion->tmp, 2);
			return (1);
		}
		else
			return (0);
	}
	return (0);
}

char		*history_expansion(char *str)
{
	t_expansion_h expansion;

	ft_bzero(&expansion, sizeof(t_expansion_h));
	if (!cheker_history_expansion(str))
		return (NULL);
	expansion.hold = ft_strdup("");
	expansion.tmp = NULL;
	while (str[expansion.i])
	{
		expansion.i++;
		if (str[expansion.i] == '!')
			while (str[expansion.i] && str[expansion.i] == '!')
				expansion.i++;
		if (!handel_history_expansion(str, &expansion))
			break ;
		expansion.j = expansion.i;
	}
	if (expansion.tmp != NULL)
		return (expansion.hold);
	ft_strdel(&(expansion.hold));
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 20:16:12 by yabakhar          #+#    #+#             */
/*   Updated: 2021/03/28 12:07:40 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

char		*get_node(char *str)
{
	t_node	*history;
	int		nuber;
	int		calc;

	history = add_to_history(NULL);
	nuber = ft_atoi(str);
	calc = calc_list(history);
	if (nuber < 0)
		nuber = calc - ft_abs(nuber);
	if (ft_abs(nuber) > calc)
	{
		ft_putstr("bash: !");
		ft_putstr(str);
		ft_putendl(": event not found");
		return (NULL);
	}
	return (get_content_in_list(nuber));
}

char		*get_all_value(int i)
{
	int		k;
	char	*node;
	char	*return_value;

	k = i;
	node = get_node("0");
	while (i > 0)
	{
		if (k == i)
			return_value = ft_strdup(node);
		else
			return_value = ft_strjoin(return_value, node);
		i--;
	}
	return (return_value);
}

char		*check_error(char *str)
{
	int		index;
	char	*index_char;

	index = 0;
	index_char = NULL;
	if (check_index_fc(str, &index))
	{
		index_char = ft_itoa(index);
		return (get_node(index_char));
	}
	else if (index2_fc(str, &index))
		return (get_content_in_list(index));
	else
	{
		ft_putstr("bash: !");
		ft_putstr(str);
		ft_putendl(": event not found");
	}
	return (NULL);
}

char		*ft_is_not_pair(int i, char *rest_value)
{
	char	*last_histroy;

	i--;
	i = i / 2;
	last_histroy = get_all_value(i);
	if (!check_error(rest_value))
	{
		ft_strdel(&last_histroy);
		return (NULL);
	}
	else if (rest_value && *rest_value)
		last_histroy = ft_freejoin(last_histroy, check_error(rest_value), 2);
	else
	{
		ft_strdel(&last_histroy);
		ft_putendl("bash: !: event not found");
	}
	return (last_histroy);
}

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
	return (ft_make_value_expansion(rest + 1, rest));
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
				expansion->hold = ft_strjoin(expansion->tmp, expansion->hold);
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

int			cheker_history_expansion(char *str)
{
	if (!ft_strcmp(str, "!"))
	{
		ft_putendl("42sh: syntax error near unexpected token `newline'");
		return (0);
	}
	return (1);
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

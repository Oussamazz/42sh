/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_expansion_tool.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <yabakhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 17:31:00 by yabakhar          #+#    #+#             */
/*   Updated: 2021/03/29 17:34:00 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int			cheker_history_expansion(char *str)
{
	if (!ft_strcmp(str, "!"))
	{
		ft_putendl("42sh: syntax error near unexpected token `newline'");
		return (0);
	}
	return (1);
}

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

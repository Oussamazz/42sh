/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 10:45:11 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/30 10:52:06 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				ft_is_expansion(char *str)
{
	if (str)
	{
		if (str[0] == '$' && ft_isalnum(str[1]) && !is_quote(str[1]))
			return (1);
	}
	return (0);
}

int				ft_is_tilde(char *str)
{
	if (str)
	{
		if (((str[0] == '~' && !is_quote(str[1]))) ||
			(str[0] == '~' && str[1] == 47))
			return (1);
	}
	return (0);
}

void			expansion_func(t_expand *v, t_env **head)
{
	if (!(v->value[v->j] = get_value_expansion(
			ft_strchr(v->arr[v->i], '$') + 1, head)))
		v->i = v->i;
	else if (v->string)
	{
		v->string = ft_freejoin(v->string, v->value[v->j], 0);
		ft_strdel(&v->value[v->j]);
	}
	else
		v->string = v->value[v->j];
	v->j++;
}

void			exp_parse_init(t_expansion *v, char **buf)
{
	if ((*buf)[(*v).i] == '$')
		(*buf)++;
	(*v).j = 0;
	(*v).buf = (*buf);
}

void			exp_chek(char *buf, t_expansion *v)
{
	while (buf[(*v).i] && !is_quote(buf[(*v).i]) &&
		!ft_is_there(" ;$|><\n\t", buf[(*v).i]) && buf[(*v).i] != '\\')
		(*v).i++;
}

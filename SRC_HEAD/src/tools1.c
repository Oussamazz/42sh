/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 11:04:58 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/30 11:07:22 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void				init_coord(t_pointt *cor)
{
	if (cor)
	{
		cor->node_index = 0;
		cor->node_addr = 0;
		cor->no_space = 0;
		cor->aggr_index = 1;
		cor->pipe_index = 1;
	}
	return ;
}

void				assign_v(t_getfullcmd *v)
{
	v->quote_opened ^= 1;
	v->flag = v->quote_opened;
	v->c = v->tmp[v->i] * v->quote_opened;
}

int					back_read(t_getfullcmd *v, int *len, char **ptr)
{
	char			*s;

	ft_move_replace(&(*v).tmp[(*v).i]);
	ft_putstr(">");
	(*ptr) = ft_readline(1);
	s = (*v).tmp;
	(*v).tmp = ft_strjoin((*v).tmp, (*ptr));
	free(s);
	(*len) += ft_strlen((*ptr));
	if (!ft_strlen((*ptr)))
	{
		free((*ptr));
		return (0);
	}
	free((*ptr));
	return (1);
}

void				backslash_checker(t_getfullcmd *v, int *len, char **tmp)
{
	while ((*v).i < (*len) && (*v).tmp[(*v).i])
	{
		if ((*v).tmp[(*v).i] == '\\' && ((*v).tmp[(*v).i + 1]
		&& ((*v).tmp[(*v).i + 1] == '\'' || (*v).tmp[(*v).i + 1] == '\"'
		|| (*v).tmp[(*v).i + 1] == '\\')))
		{
			(*v).i += 2;
			if ((*v).i >= (*len))
				break ;
			continue ;
		}
		else if (((*v).tmp[(*v).i] == '\\' && !(*v).tmp[(*v).i + 1]))
		{
			if (!back_read(v, len, tmp))
				break ;
			continue ;
		}
		if (is_quote((*v).tmp[(*v).i]) &&
		((*v).c == (*v).tmp[(*v).i] || (*v).c == 0))
			assign_v(v);
		(*v).i++;
	}
}

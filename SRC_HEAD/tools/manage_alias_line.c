/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_alias_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:25:08 by afaragi           #+#    #+#             */
/*   Updated: 2021/03/29 16:24:01 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		get_start_end_line(t_a_v *vars, char **line, int e, t_alias **alias)
{
	(*vars).ptr = (*vars).head->name;
	(*vars).head->name = ft_strdup("#");
	ft_strdel(&(*vars).ptr);
	(*vars).value = return_value((*vars).tmp, (*alias));
	(*vars).endline = ft_strdup_from_to((*line), e, ft_strlen((*line)));
	if ((*vars).start > 0 && (*line)[(*vars).start] == ' ')
		(*vars).start++;
	(*vars).startline = ft_strdup_from_to((*line), 0, (*vars).start);
}

int			if_no_start_line(t_a_v *vars, char **line, int *s, int *e)
{
	if ((*vars).value)
	{
		(*vars).ptr = (*line);
		(*line) = ft_strjoin((*vars).value, (*line));
		ft_strdel(&(*vars).ptr);
	}
	ft_strdel(&(*vars).tmp);
	if ((*vars).catch)
	{
		(*e) = (*vars).start + ft_strlen((*vars).value);
		(*vars).tmp = ft_strdup_from_to((*line), (*vars).start, (*e));
		(*s) = (*vars).start;
		clean_vars(vars, 0);
		return (1);
	}
	ft_strdel(&(*vars).value);
	free_alias_list(&(*vars).catch, del);
	ft_strdel(&(*vars).endline);
	ft_strdel(&(*vars).startline);
	return (0);
}

int			if_there_start_line(t_a_v *vars, char **line, int *s, int *e)
{
	(*vars).ptr = (*line);
	(*line) = ft_strjoin((*vars).startline, (*vars).value);
	ft_strdel(&(*vars).ptr);
	if ((*vars).endline)
	{
		(*vars).ptr = (*line);
		(*line) = ft_strjoin((*line), (*vars).endline);
		ft_strdel(&(*vars).ptr);
	}
	if ((*vars).catch)
	{
		ft_strdel(&(*vars).tmp);
		(*e) = (*vars).start + ft_strlen((*vars).value);
		(*vars).tmp = ft_strdup_from_to((*line), (*vars).start, (*e));
		(*s) = (*vars).start;
		ft_strdel(&(*vars).value);
		ft_strdel(&(*vars).endline);
		ft_strdel(&(*vars).startline);
		return (1);
	}
	return (0);
}

void		replace_line(int *s, int e, char **line)
{
	while ((*s) < e)
	{
		ft_move_replace((*line));
		(*s)++;
	}
}

void		printfx(char **line, int s, int e, t_alias **alias)
{
	t_a_v vars;

	init_alias(&vars, s, e, line);
	vars.catch = copy_list((*alias));
	vars.head = vars.catch;
	while (vars.tmp && (vars.head = check_alias_repeate(vars.tmp, vars.catch)))
	{
		get_start_end_line(&vars, line, e, alias);
		replace_line(&s, e, line);
		if (!vars.startline)
		{
			if (if_no_start_line(&vars, line, &s, &e))
				continue ;
			else
				return ;
		}
		else if (if_there_start_line(&vars, line, &s, &e))
			continue ;
		clean_vars(&vars, 1);
	}
	free_alias_list(&vars.catch, del);
	ft_strdel(&vars.tmp);
}

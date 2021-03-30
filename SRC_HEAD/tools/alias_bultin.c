/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_bultin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:26:08 by afaragi           #+#    #+#             */
/*   Updated: 2021/03/30 11:09:48 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		init_alias(t_a_v *vars, int s, int e, char **line)
{
	(*vars).start = s;
	(*vars).tmp = ft_strdup_from_to((*line), s, e);
	(*vars).ptr = (*vars).tmp;
	(*vars).tmp = ft_strtrim((*vars).tmp);
	ft_strdel(&(*vars).ptr);
}

int			if_del_found(t_c_v *var, char **line)
{
	if ((*line)[(*var).i] == ';' || (*line)[(*var).i] == '|' ||
		!ft_strncmp(&(*line)[(*var).i], "&&", 2) ||
			!ft_strncmp(&(*line)[(*var).i], "||", 2))
	{
		if (!ft_strncmp(&(*line)[(*var).i], "&&", 2) ||
			!ft_strncmp(&(*line)[(*var).i], "||", 2))
			(*var).i += 2;
		else
			(*var).i++;
		(*var).old_i = (*var).i;
		if (!(*line)[(*var).i])
			return (1);
		while (is_blank((*line)[(*var).i]))
			(*var).i++;
		(*var).flag ^= 1;
	}
	return (0);
}

int			check_line_var(t_c_v *var, t_alias **alias, char **line)
{
	if ((is_indice((*line)[(*var).i]) ||
		(!ft_strncmp(&(*line)[(*var).i], "&&", 2) ||
			!ft_strncmp(&(*line)[(*var).i], "||", 2))) && (*var).flag)
	{
		printfx(line, (*var).old_i, (*var).i, alias);
		(*var).old_i = (*var).i;
		(*var).flag = 0;
	}
	if (if_del_found(var, line))
		return (1);
	return (0);
}

void		alias_check(char **line, t_alias **alias)
{
	t_c_v var;

	var.i = 0;
	var.old_i = var.i;
	var.flag = 1;
	var.ptr = (*line);
	(*line) = ft_strtrim((*line));
	ft_strdel(&var.ptr);
	if ((*line))
	{
		while ((*line)[var.i])
		{
			if (check_line_var(&var, alias, line))
				break ;
			var.i++;
		}
		if (var.old_i != var.i && var.flag)
			printfx(line, var.old_i, var.i, alias);
	}
}

void		alias_bultin(char **line, t_alias **alias)
{
	int i;

	i = 1;
	if (!line[1])
		get_value_from_list(line[0], (*alias), 1);
	if (line)
	{
		while (line[i])
		{
			if (ft_strchr(line[i], '='))
				add_to_alias_file(line[i], alias);
			else
				get_value_from_list(ft_strtrim(line[i]), (*alias), 0);
			i++;
		}
	}
}

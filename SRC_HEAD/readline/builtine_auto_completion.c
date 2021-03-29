/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtine_auto_completion.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <yabakhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 11:18:05 by yabakhar          #+#    #+#             */
/*   Updated: 2021/03/29 13:18:28 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void		all_bin_files(char *str, t_line *line, int flag, t_affcmpl **afcmp)
{
	DIR				*dir;
	struct dirent	*dent;

	if ((dir = opendir(str)))
	{
		while ((dent = readdir(dir)) != NULL)
		{
			if ((flag && !ft_strncmp(line->compl.search, dent->d_name,
				line->compl.len)) || !flag)
			{
				if (!ft_strequ(dent->d_name, ".") &&
					!ft_strequ(dent->d_name, ".."))
				{
					(*afcmp)->content = ft_strdup(dent->d_name);
					(*afcmp)->next = ft_memalloc(sizeof(t_affcmpl));
					(*afcmp) = (*afcmp)->next;
					line->compl.count++;
				}
			}
		}
		closedir(dir);
	}
}

void		ft_reaffiche_prompte(t_line *line)
{
	tputs(tgoto(tgetstr("cm", 0), 0, line->c_o.y), 0, ft_output);
	tputs(tgetstr("cd", 0), 0, ft_output);
	ft_prompte();
	tputs(tgoto(tgetstr("cm", 0), line->c_o.x, line->c_o.y), 0, ft_output);
	print_line(g_str);
	move_cursor_v(line);
	cur_goto(line, line->cursor);
}

void		make_path_parameters(t_line *line)
{
	if (line->compl.str[0] == '$' && line->compl.str[1] == '{' &&
		line->compl.str[2] != '{')
	{
		line->compl.search = ft_strdup(ft_strrchr(line->compl.str, '{') + 1);
		line->compl.bracket = 1;
	}
	else if (ft_strchr(line->compl.str, '$'))
		line->compl.search = ft_strdup(ft_strrchr(line->compl.str, '$') + 1);
}

void		free_list(t_affcmpl *affcmpl, t_affcmpl *affcmpltmp)
{
	while (affcmpl)
	{
		affcmpltmp = affcmpl;
		(affcmpl) = (affcmpl)->next;
		free((affcmpltmp)->content);
		free(affcmpltmp);
	}
}

void		ft_builtine_parameter_file(t_line *line, char **str)
{
	t_affcmpl *affcmpl;
	t_affcmpl *affcmpltmp;

	affcmpl = ft_memalloc(sizeof(t_affcmpl));
	affcmpltmp = affcmpl;
	if (line->compl.type == 1)
	{
		make_path_parameters(line);
		stock_path_paramters(line, &affcmpltmp);
	}
	else if (line->compl.type == 2)
	{
		make_path_file(line, 0);
		stock_path_file(line->compl.path, line, &affcmpltmp);
	}
	if (line->compl.count > 1)
		completion_files(affcmpl, line);
	else if (line->compl.count == 1)
		completion_str(affcmpl, line, str);
	free_list(affcmpl, affcmpltmp);
}

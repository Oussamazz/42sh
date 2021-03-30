/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <yabakhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 12:17:19 by yabakhar          #+#    #+#             */
/*   Updated: 2021/03/29 17:26:08 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void		ft_parce_completion(t_line *line, char **str)
{
	int		cursor_pos;
	char	*lastchar;
	char	*prefix;

	cursor_pos = line->c_len - (1 * (line->c_len > 0));
	prefix = ft_strrsearch(*str, " ;&$|", cursor_pos);
	line->compl.prefix_pos = prefix - (*str);
	get_str_for_search(*str, line, line->c_len);
	if (*prefix == '$')
		line->compl.type = 1;
	else
	{
		lastchar = ft_strrsearch2(*str, " ", line->compl.prefix_pos);
		if (is_in_str(*lastchar, " &|;") || lastchar == str[0])
			line->compl.type = 0;
		else
			line->compl.type = 2;
	}
	line->compl.bracket = 0;
}

void		completion_str(t_affcmpl *head, t_line *line, char **str)
{
	int		plus_len;
	char	*third_str;
	char	*second_str;
	char	*tmp;

	plus_len = ft_strlen(head->content) - line->compl.len;
	third_str = ft_strsub(*str, line->cursor, line->b_line - line->cursor);
	second_str = ft_strsub(*str, 0, line->cursor - line->compl.len);
	tmp = ft_freejoin(second_str, head->content, 0);
	ft_strdel(str);
	*str = ft_freejoin(tmp, third_str, 2);
	line->b_line += plus_len;
	line->len += plus_len;
	line->cursor += plus_len;
	ft_multilne(*str, line);
	line->c_len += plus_len;
	ft_clear(line, *str);
}

void		stock_path_paramters(t_line *line, t_affcmpl **affcmpl)
{
	t_envv	*list;
	int		flag;

	list = g_set;
	line->compl.count = 0;
	line->compl.len = ft_strlen(line->compl.search);
	flag = (!line->compl.len) ? 0 : 1;
	while (list)
	{
		if ((flag && !ft_strncmp(line->compl.search, list->name,
			line->compl.len)) || !flag)
		{
			(*affcmpl)->content = ft_strdup(list->name);
			(*affcmpl)->next = ft_memalloc(sizeof(t_affcmpl));
			(*affcmpl) = (*affcmpl)->next;
			line->compl.count++;
		}
		list = list->next;
	}
}

void		make_path_completion(t_line *line, char **str)
{
	if (!line->compl.type)
	{
		make_path_file(line, 1);
		ft_get_all_bin_dirs(line, str);
	}
	else if (line->compl.type >= 1)
		ft_builtine_parameter_file(line, str);
}

void		ft_auto_completion(t_line *line, char **str)
{
	char	*tmp;

	ft_parce_completion(line, str);
	tmp = ft_strdup(line->compl.str);
	ft_strdel(&line->compl.str);
	line->compl.str = ft_strtrim(tmp);
	ft_strdel(&(tmp));
	make_path_completion(line, str);
	if (line->compl.str)
		ft_strdel(&(line->compl.str));
	if (line->compl.search)
		ft_strdel(&(line->compl.search));
	if (line->compl.path)
		ft_strdel(&(line->compl.path));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_r_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <yabakhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 17:38:44 by yabakhar          #+#    #+#             */
/*   Updated: 2021/03/29 17:42:15 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void		load_hsitory(const char *file)
{
	char	*line;
	int		num;
	int		fd;

	num = 0;
	line = NULL;
	if ((fd = open(file, O_RDWR | O_CREAT, 00600)) == -1)
		return ;
	while (get_next_line(fd, &line) > 0)
	{
		add_to_history(line);
		ft_strdel(&line);
		num++;
	}
	ft_strdel(&line);
	close(fd);
	g_lohtory = 1;
}

void		update_cur_mode_r(t_line *line, int prompt_len)
{
	int		len;
	int		cur_update_mode_r;

	len = 0;
	if (line->mode_r.s && *line->mode_r.s)
		len = ft_strlen(line->mode_r.s) + prompt_len;
	else
		len = prompt_len;
	cur_update_mode_r = (len / line->col);
	if ((len % line->col) > 0)
		cur_update_mode_r += 1;
	cur_update_mode_r += line->mode_r.y;
	if ((cur_update_mode_r - line->row) > 0)
	{
		line->c_o.y = line->c_o.y - (cur_update_mode_r - line->row);
		line->mode_r.y = line->mode_r.y - (cur_update_mode_r - line->row);
		tputs(tgoto(tgetstr("cm", 0), 0, line->mode_r.y), 0, ft_output);
		ft_putchar('\n');
		move_cursor_v(line);
	}
}

void		ft_disable_mode_r(t_line *line)
{
	if (line->mode_r.flag)
	{
		tputs(tgoto(tgetstr("cm", 0), 0, line->mode_r.y), 0, ft_output);
		tputs(tgetstr("cd", 0), 0, ft_output);
		if (line->mode_r.s && *line->mode_r.s)
			ft_strdel(&line->mode_r.s);
		cur_goto(line, line->cursor);
		line->mode_r.flag = 0;
	}
}

int			get_index_mode_r(t_line *line, int *index)
{
	t_node	*node;
	int		i;

	i = 0;
	*index = 0;
	node = add_to_history(NULL);
	while (node)
	{
		i++;
		if (ft_strstr(node->content, line->mode_r.s))
		{
			*index = i;
			break ;
		}
		node = node->next;
	}
	if ((*index) > 0)
		return (1);
	else
		return (0);
}

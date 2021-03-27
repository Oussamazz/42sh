/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_r.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 14:50:24 by yabakhar          #+#    #+#             */
/*   Updated: 2021/02/04 12:53:29 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void load_hsitory(const char *file)
{
	char *line;
	int num;
	int fd;

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

void update_cur_mode_r(t_line *line, int prompt_len)
{
	int len;
	int cur_update_mode_r;

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

void ft_disable_mode_r(t_line *line)
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

int get_index_mode_r(t_line *line, int *index)
{
	t_node *node;
	int i;

	i = 0;
	*index = 0;
	node = add_to_history(NULL);
	while (node)
	{
		i++;
		if (ft_strstr(node->content, line->mode_r.s))
		{
			*index = i;
			break;
		}
		node = node->next;
	}
	if ((*index) > 0)
		return (1);
	else
		return (0);
}

void mode_r(t_line *line)
{
	if (!line->mode_r.flag)
	{
		if (line->mode_r.s && *line->mode_r.s)
			ft_strdel(&line->mode_r.s);
		line->mode_r.y = line->c_o.y + count_row(line);
		update_cur_mode_r(line, 14);
		tputs(tgoto(tgetstr("cm", 0), 0, line->mode_r.y), 0, ft_output);
		move_cursor_v(line);
		prompte_mode_r(0, &line->mode_r.s);
		ft_putstr("bck-i-search: ");
		line->mode_r.flag = 1;
	}
}

void prompte_mode_r(char c, char **str)
{
	char ttab[2];

	ttab[0] = c;
	ttab[1] = '\0';
	if (str && *str)
		*str = ft_freejoin(*str, ttab, 0);
	else if (str && !*str)
		*str = ft_strdup(ttab);
}

void print_prompte_(t_line *line, int error)
{
	line->mode_r.y = line->c_o.y + count_row(line);
	tputs(tgoto(tgetstr("cm", 0), 0, line->mode_r.y), 0, ft_output);
	tputs(tgetstr("cd", 0), 0, ft_output);
	if (error)
		ft_putstr("failing ");
	ft_putstr("bck-i-search: ");
	ft_putstr(line->mode_r.s);
	ft_putchar(' ');
}

void search_mode_r(t_line *line, t_node **current)
{
	t_node *node;
	int k;

	k = 0;
	node = NULL;
	line->mode_r.tmp = line->r;
	prompte_mode_r(line->mode_r.tmp, &line->mode_r.s);
	if (get_index_mode_r(line, &k))
	{
		node = add_to_history(NULL);
		while (--k > 0)
			node = (node)->next;
		*current = node;
		tputs(tgoto(tgetstr("cm", 0), line->c_o.x, line->c_o.y), 0, ft_output);
		tputs(tgetstr("cd", 0), 0, ft_output);
		ft_history_goto(current, (*current), line);
		line->mode_r.y = line->c_o.y + count_row(line);
		update_cur_mode_r(line, 14);
		print_prompte_(line, 0);
	}
	else
	{
		update_cur_mode_r(line, 22);
		print_prompte_(line, 1);
	}
}

void delet_mode_r(char **str, t_line *line)
{
	char *tmp;
	int len;

	len = ft_strlen(*str);
	if (!len)
		return;
	tmp = ft_strsub(*str, 0, len - 1);
	ft_strdel(str);
	*str = ft_strdup(tmp);
	ft_strdel(&tmp);
	tputs(tgoto(tgetstr("cm", 0), 0, line->mode_r.y), 0, ft_output);
	tputs(tgetstr("cd", 0), 0, ft_output);
	if (!(get_index_mode_r(line, &len)))
		ft_putstr("failing ");
	ft_putstr("bck-i-search: ");
	ft_putstr(line->mode_r.s);
}

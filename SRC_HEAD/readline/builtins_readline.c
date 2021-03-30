/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_readline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <yabakhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 14:27:02 by yabakhar          #+#    #+#             */
/*   Updated: 2021/03/29 17:50:17 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int		keyshandle3(t_line *line, char **str)
{
	int r;

	r = 0;
	if (line->r == DEL && !line->mode_r.flag && (r = 1))
		ft_delet(str, line);
	else if (line->r == DEL && line->mode_r.flag && (r = 1))
		delet_mode_r(&line->mode_r.s, line);
	else if (line->r == TAB && !line->mode_r.flag && (r = 1))
		ft_auto_completion(line, str);
	return (r);
}

int		keyshendle2(t_line *line, char **str, int flag)
{
	int r;

	r = 0;
	if (!line->mode_r.flag)
	{
		if (line->r == ALT_RTH && (r = 1))
			ft_alt_rth(*str, line);
		else if (line->r == ALT_LFT && (r = 1))
			ft_alt_lft(*str, line);
		else if (line->r == CTRL_L && (r = 1))
			ft_ctl_l(line, *str);
		else if (line->r == ALT_D && (!line->b_line))
			ft_ctl_d(flag);
	}
	return (r);
}

int		keyshendle1(t_line *line, char **str, t_node **current)
{
	int r;

	r = 0;
	if (!line->mode_r.flag)
	{
		if ((line->r == HOME || line->r == DEEP) && (r = 1))
			home_deep(line, *str);
		else if (line->r == UP && (r = 1))
			ft_history_goto(current, (*current)->next, line);
		else if (line->r == DOWN && (r = 1))
			ft_history_goto(current, (*current)->prev, line);
		else if (line->r == PAGE_DOWN && (r = 1))
			move_down(line);
		else if (line->r == PAGE_UP && (r = 1))
			move_up(line);
		else if (line->r == CTRL_R && !line->mode_r.flag && (r = 1))
			mode_r(line);
	}
	return (r);
}

int		keyshendle(t_line *line, char **str)
{
	int r;

	r = 0;
	if (line->r == LEFT && (r = 1))
		move_left(line, *str);
	else if (line->r == RIGHT && (r = 1))
		move_right(line, *str);
	if (!line->mode_r.flag)
	{
		if (line->r == ALT_V && line->sltstr && (r = 1))
		{
			line->slct = 0;
			line->slctd = 0;
			line->slctf = 0;
			ft_print_print(str, line, line->sltstr);
		}
		else if (line->r == ALT_S && (r = 1))
			ft_chack_selction(line, *str);
		else if (line->r == ALT_C && (r = 1))
			ft_copie(line, *str);
	}
	return (r);
}

int		ft_readline_builtines(int flag, char *buff, t_line *line,
	t_node **current)
{
	if (keyshendle(line, &(*current)->tmp))
		return (1);
	else if (!line->slct && keyshendle1(line, &(*current)->tmp, current))
		return (1);
	else if (!line->slct && keyshendle2(line, &(*current)->tmp, flag))
		return (1);
	else if (!line->slct && keyshandle3(line, &(*current)->tmp))
		return (1);
	else if ((line->r == END && line->slct == 0) || g_clt_c == 1)
		return (0);
	else if (line->slct == 0 && !line->mode_r.flag)
	{
		ft_print_print(&(*current)->tmp, line, buff);
		return (1);
	}
	else if (line->slct == 0 && line->mode_r.flag && CTRL_R != line->r)
	{
		search_mode_r(line, current);
		return (1);
	}
	return (1);
}

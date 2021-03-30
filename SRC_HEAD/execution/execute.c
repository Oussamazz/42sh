/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 03:16:16 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/30 10:36:37 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				append_redir(t_redir *redirection, t_redir *prev)
{
	int			fd;
	int			left;
	char		*left_fd;
	char		*right_fd;

	left_fd = NULL;
	right_fd = NULL;
	if (redirection)
		right_fd = redirection->next->rfd;
	if (prev)
		left_fd = prev->lfd;
	if ((fd = open(right_fd, O_CREAT | O_WRONLY | O_APPEND, 0644)) == -1)
		return (-1);
	if (left_fd)
	{
		if (ft_str_is_digit(left_fd))
			left = ft_atoi(left_fd);
		else
			return (ft_putendl_fd_int("42sh: Error: Left redirection.", 2, -1));
		dup2(fd, left);
	}
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (fd);
}

int				execute_redirection(t_redir *redirections, char *tty_name)
{
	t_redir		*prev;
	int			fd;

	fd = 0;
	prev = NULL;
	if (!tty_name)
		exit(1);
	while (redirections != NULL)
	{
		if (redirections->sym && ft_is_there(redirections->sym, '&'))
			fd = agg_redirection(redirections, prev, fd);
		else if (redirections->sym && (ft_strequ(redirections->sym, ">") ||
			ft_strequ(redirections->sym, "<")))
			fd = ft_redirect_in_out(redirections, prev, fd);
		else if (redirections->sym && (ft_strequ(redirections->sym, ">>")))
			fd = append_redir(redirections, prev);
		else if (redirections->sym && (ft_strequ(redirections->sym, "<<")))
			fd = here_document(redirections, g_tty_name);
		if (fd < 0)
			break ;
		prev = redirections;
		redirections = redirections->next;
	}
	return (fd);
}

t_miniast		*advance_tree(t_miniast *tree)
{
	while (tree)
	{
		if (tree->sep)
		{
			while ((!g_the_status && tree->logic_op == OR) ||
				(g_the_status && tree->logic_op == AND))
				tree = tree->sep;
			return (tree->sep);
		}
		tree = tree->pipe;
	}
	return (tree);
}

t_miniast		*tree_advance(t_miniast *tree)
{
	if (!tree->sep)
		tree = advance_tree(tree);
	else
	{
		while ((!g_the_status && tree->logic_op == OR) ||
			(g_the_status && tree->logic_op == AND))
			tree = tree->sep;
		tree = tree->sep;
	}
	return (tree);
}

int				execute(t_miniast *tree, t_env **env_list)
{
	char		**tabs;
	int			fd;
	char		*line;

	fd = 0;
	line = NULL;
	tabs = g_settab;
	while (tree != NULL && tree->cmd[0])
	{
		if (tree->cmd[0][0] == '!' && tree->cmd[0][1] && !tree->pipe)
		{
			line = history_expansion(tree->cmd[0]);
			if (line)
				execute_fc(line);
			ft_strdel(&line);
		}
		else if (tree->cmd && tree->cmd[0] &&
			check_builtins_nfrk(tree->cmd[0]) && !tree->pipe)
			execute_blt_with_fork(tree, env_list);
		else
			execute_pipes(tree, tabs, env_list);
		tree = tree_advance(tree);
	}
	return (1);
}

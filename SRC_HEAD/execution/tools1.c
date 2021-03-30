/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 10:36:40 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/30 10:37:59 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				ft_redirect_in_out_2(int fd, char *left_fd,
	t_redir *redirections)
{
	int			left;

	left = 0;
	if (left_fd)
	{
		if (ft_str_is_digit(left_fd))
			left = ft_atoi(left_fd);
		else
		{
			ft_putstr_fd(ERROR4, 2);
			ft_putendl_fd(ERROR44, 2);
			return (-1);
		}
		dup2(fd, left);
	}
	else
	{
		if (!ft_strcmp(redirections->sym, ">"))
			dup2(fd, STDOUT_FILENO);
		else if (!ft_strcmp(redirections->sym, "<"))
			dup2(fd, STDIN_FILENO);
	}
	close(fd);
	return (0);
}

int				ft_redirect_in_out(t_redir *redirections, t_redir *prev, int fd)
{
	char		*right_fd;
	char		*left_fd;

	left_fd = NULL;
	if (redirections->next)
		right_fd = redirections->next->rfd;
	if (prev)
		left_fd = prev->lfd;
	if (ft_strcmp(redirections->sym, ">") == 0 && right_fd)
		fd = open(right_fd, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (right_fd)
	{
		fd = open(right_fd, O_RDONLY);
		if (fd < 0)
		{
			ft_putendl_fd_error("42sh: No such file or directory: ", right_fd,
				"\n", NULL);
			exit(0);
			return (fd);
		}
	}
	ft_redirect_in_out_2(fd, left_fd, redirections);
	return (255);
}

void			blt_check(t_miniast *tree, t_env **env_list)
{
	if (ft_strequ(tree->cmd[0], "echo"))
		blt_echo(tree->cmd, tree->redirection);
	else if (ft_strequ(tree->cmd[0], "fg"))
		fg_blt(tree->cmd);
	else if (ft_strequ(tree->cmd[0], "unalias"))
		delete_alias_var(&g_alias, tree->cmd);
	else if (ft_strequ(tree->cmd[0], "alias"))
		alias_bultin(tree->cmd, &g_alias);
	else if (ft_strequ(tree->cmd[0], "bg"))
		bg_blt(tree->cmd);
	else if (ft_strequ(tree->cmd[0], "jobs"))
		jobs_blt(tree->cmd);
	else if (ft_strequ(tree->cmd[0], "env"))
		print_env_list(env_list);
	else if (ft_strequ(tree->cmd[0], "type"))
		type_builtin(tree->cmd, env_list);
	else if (ft_strequ(tree->cmd[0], "cd"))
		blt_cd(tree->cmd, env_list);
	else if (ft_strequ(tree->cmd[0], "fc"))
		parce_param_fc(tree->cmd);
	else if (ft_strequ(tree->cmd[0], "export"))
		ft_export(tree->cmd);
	else if (ft_strequ(tree->cmd[0], "unset"))
		blt_unsetenv(tree->cmd, env_list);
}

void			execute_blt_with_fork(t_miniast *tree, t_env **env_list)
{
	if (tree->cmd && *env_list)
	{
		if (ft_strequ(tree->cmd[0], "set"))
		{
			ft_listtotab();
			ft_putdblstr(g_settab);
		}
		else if (ft_strequ(tree->cmd[0], "hash"))
			ft_hash(tree->cmd, &g_hashtable);
		else if (ft_strequ(tree->cmd[0], "test"))
			g_the_status = ft_test(tree->cmd);
		else if (ft_strequ(tree->cmd[0], "exit"))
		{
			print_in_history(PATH_HISTORY_FILE);
			add_alias_list_to_file(g_alias);
			free_alias_list(&g_alias, del);
			exit_blt(tree->cmd);
		}
		else
			blt_check(tree, env_list);
	}
}

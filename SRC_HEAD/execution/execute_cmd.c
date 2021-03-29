/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 18:10:21 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/29 16:45:45 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				check_builtins(char *cmd_name)
{
	if (ft_strequ(cmd_name, "jobs") || ft_strequ(cmd_name, "alias") ||
		ft_strequ(cmd_name, "echo") || ft_strequ(cmd_name, "set")
		|| ft_strequ(cmd_name, "fg") ||
		ft_strequ(cmd_name, "unset") || ft_strequ(cmd_name, "env") ||
		ft_strequ(cmd_name, "cd") || ft_strequ(cmd_name, "type") ||
			ft_strequ(cmd_name, "exit") || ft_strequ(cmd_name, "fc") ||
			ft_strequ(cmd_name, "hash") || ft_strequ(cmd_name, "test"))
		return (1);
	return (0);
}

void			my_execve(const char *file_name, char **cmd, char **tabs)
{
	if (access(file_name, X_OK) == 0)
	{
		if (execve(file_name, cmd, tabs) == -1)
			ft_putendl_fd("42sh: Error: Execution Failed.", 2);
	}
	else
		ft_putendl_fd_error("42sh: permission denied: ",
			cmd[0], "\n", NULL);
	return ;
}

void			execute_direct(char **cmd, char **tabs)
{
	const char	*file_name;

	if (cmd[0][0] == '.' && cmd[0][1] == '/')
		file_name = ft_strrchr(cmd[0], '/') + 1;
	else
		file_name = cmd[0];
	if (access(file_name, F_OK) == 0)
		my_execve(file_name, cmd, tabs);
	else
		ft_putendl_fd_error("42sh: no such file or directory: ",
			cmd[0], "\n", NULL);
}

void			execute_undirect(char **cmd, char **tabs, t_env **env)
{
	char		*bin_file;
	char		*print;

	(void)env;
	print = NULL;
	bin_file = g_binfile;
	if (access(bin_file, F_OK) == 0)
		my_execve(bin_file, cmd, tabs);
	else
		ft_putendl_fd_error("42sh: no such file or directory: ",
			cmd[0], "\n", NULL);
	if (print)
		ft_strdel(&print);
}

char			*get_bin_file(char **cmd, t_env **env)
{
	t_get_bin	v;

	ft_bzero(&v, sizeof(t_get_bin));
	if (!(v.env_path_value = get_value_expansion("PATH", env)))
		return (NULL);
	if (!(v.dirs = ft_strsplit(v.env_path_value, ':')))
		return (NULL);
	ft_strdel(&v.env_path_value);
	v.i = -1;
	while (v.dirs[++v.i] != NULL)
	{
		if (!(v.tmp = ft_strdup(v.dirs[v.i])))
			return (NULL);
		v.tmp2 = ft_freejoin(v.tmp, "/", 0);
		if (!(v.bin_file = ft_strjoin(v.tmp2, cmd[0])))
			return (NULL);
		ft_strdel(&v.tmp2);
		if (access(v.bin_file, F_OK) == 0)
			break ;
		ft_strdel(&v.bin_file);
	}
	ft_free_arr(v.dirs);
	return (v.bin_file);
}

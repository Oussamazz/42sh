/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 17:32:52 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/30 10:37:47 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int		check_varname(char *cmd)
{
	int			i;

	i = 0;
	if (!cmd || !ft_isalpha(*cmd))
		return (0);
	while (cmd[i])
	{
		if (i && !ft_isalnum(cmd[i]))
			return (0);
		i++;
	}
	return (1);
}

int				check_args_no(char **cmd)
{
	int			i;

	i = 0;
	while (cmd[i++] != NULL)
		;
	return (i - 1);
}

void			blt_unsetenv(char **cmd, t_env **env_list)
{
	int			i;

	if (check_args_no(cmd) < 2)
		return (ft_putendl_fd("42sh: Error: [unsetenv [var_name] ...].", 2));
	i = 1;
	while (cmd[i])
	{
		deletenode(env_list, cmd[i]);
		ft_varchr(cmd[i], DELL);
		i++;
	}
	return ;
}

void			blt_setenv(char **cmd, t_env **env_list)
{
	if ((check_args_no(cmd)) == 1)
		return (print_env_list(env_list));
	if ((check_args_no(cmd)) != 3)
		return (ft_putendl_fd(ERROR1, 2));
	else if (!check_varname(cmd[1]))
	{
		ft_putstr_fd(ERROR2, 2);
		ft_putendl_fd(ERROR22, 2);
		return ;
	}
	if (env_exist(env_list, cmd[1]) == 0)
		addtolist(env_list, ft_strdup(cmd[1]), ft_strdup(cmd[2]));
	else
		modify_env(env_list, cmd[1], cmd[2]);
	return ;
}

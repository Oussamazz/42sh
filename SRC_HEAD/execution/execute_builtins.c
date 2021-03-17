/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 17:32:52 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/11 16:11:42 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int		check_varname(char *cmd)
{
	int		i;

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
		return (ft_putendl_fd("21sh: Error: [unsetenv [var_name] ...].", 2));
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
	//dprintf(2, "added\n");
	return ;
}

void			execute_blt_with_fork(t_miniast *tree, char **tabs, t_env **env_list)
{
	if (tree->cmd && tabs && *env_list)
	{
		if (ft_strequ(tree->cmd[0], "echo"))
			blt_echo(tree->cmd);
		else if (ft_strequ(tree->cmd[0], "fg"))
			fg_blt(tree->cmd);
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
		else if (ft_strequ(tree->cmd[0], "set"))
			ft_putdblstr(g_settab);
		else if (ft_strequ(tree->cmd[0], "exit"))
		{
			print_in_history(PATH_HISTORY_FILE);
			exit(0);
		}
	}
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 17:44:10 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/25 13:04:53 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			gen_oldpwd(char *cwd, t_env **env_list)
{
	bool		flag;
	char		*cwd_;
	char		*cmd[4];

	flag = false;
	cwd_ = NULL;
	if (cwd == NULL)
	{
		if (!(cwd_ = get_value_expansion_cd("PWD", env_list)))
			return ;
		cwd = cwd_;
		flag = true;
	}
	// ft_newvar(cwd, NOT_IN_ENV);
	cmd[0] = "setenv";
	cmd[1] = "OLDPWD";
	cmd[2] = cwd;
	cmd[3] = NULL;
	blt_setenv(cmd, env_list);
	if (flag)
		ft_strdel(&cwd_);
	return ;
}

void			gen_pwd(char *new_path, t_env **env_list)
{
	char		*cmd[4];

	if (new_path == NULL)
		return ;
	// ft_newvar(new_path, NOT_IN_ENV);
	cmd[0] = "setenv";
	cmd[1] = "PWD";
	cmd[2] = new_path;
	cmd[3] = NULL;
	blt_setenv(cmd, env_list);
	return ;
}

void			print_env_list(t_env **head)
{
	t_env		*tmp;

	tmp = *head;
	while (tmp)
	{
		ft_putstr_fd(tmp->env_var_name, 1);
		ft_putstr_fd("=", 1);
		ft_putendl_fd(tmp->env_var_value, 1);
		tmp = tmp->next;
	}
}

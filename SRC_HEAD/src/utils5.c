/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 17:44:10 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/29 15:58:28 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			ft_update(char *all, char *name)
{
	t_envv		*tmp;

	tmp = NULL;
	if ((tmp = ft_varchr(name, SEARCH)))
		ft_newvar(all, tmp->type);
	else
		ft_newvar(all, NOT_IN_ENV);
}

void			gen_oldpwd(char *cwd, t_env **env_list)
{
	bool		flag;
	char		*cwd_;
	char		*tmp;

	flag = false;
	cwd_ = NULL;
	tmp = NULL;
	if (cwd == NULL)
	{
		if (!(cwd_ = get_value_expansion_cd("PWD", env_list)))
			return ;
		cwd = cwd_;
		flag = true;
	}
	tmp = ft_strjoin("OLDPWD=", cwd);
	ft_update(tmp, "OLDPWD");
	ft_strdel(&tmp);
	if (flag)
		ft_strdel(&cwd_);
	return ;
}

void			gen_pwd(char *new_path, t_env **env_list)
{
	char		*tmp;

	(void)env_list;
	tmp = NULL;
	if (new_path == NULL)
		return ;
	tmp = ft_strjoin("PWD=", new_path);
	ft_update(tmp, "PWD");
	ft_strdel(&tmp);
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

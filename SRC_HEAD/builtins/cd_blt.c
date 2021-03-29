/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_blt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 17:59:22 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/29 18:50:54 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void		cd_simple(char *path, t_env **env_list)
{
	t_cd_smpl cd;

	if (path && access(path, F_OK) == 0)
	{
		stat(path, &cd.st);
		if (!S_ISDIR(cd.st.st_mode) && ft_strrchr(path, '/'))
		{
			ft_putendl_fd_error("42sh: cd: not a directory: ",
				ft_strrchr(path, '/') + 1, "\n", NULL);
			return ;
		}
		if (access(path, X_OK) == 0)
		{
			gen_oldpwd((cd.tmp = get_cwd()), env_list);
			chdir(path);
			gen_pwd((cd.tmp2 = get_cwd()), env_list);
			ft_strdel_2(&cd.tmp, &cd.tmp2);
		}
		else if (ft_strrchr(path, '/'))
			ft_putendl_fd_error(ERROR5, ft_strrchr(path, '/') + 1, "\n", NULL);
	}
	else if (ft_strrchr(path, '/'))
		ft_putendl_fd_error(ERROR6, ft_strrchr(path, '/') + 1, "\n", NULL);
	else
		ft_putendl_fd_error(ERROR6, path, "\n", NULL);
}

static void		cd_home(t_env **env_list)
{
	char		*home;

	home = NULL;
	if (!(home = get_value_expansion_cd("HOME", env_list)))
		return ;
	cd_simple(home, env_list);
	ft_strdel(&home);
}

static void		cd_back(t_env **env_list)
{
	char		*back_path;

	back_path = NULL;
	if (!(back_path = get_value_expansion_cd("OLDPWD", env_list)))
		return ;
	cd_simple(back_path, env_list);
	ft_strdel(&back_path);
}

int				check_args(char **cmd, t_env **env_list, int *i)
{
	if (check_args_no(cmd) > 3)
	{
		g_the_status = 1;
		ft_putendl_fd("42sh: cd: Too many arguments.", 2);
		return (1);
	}
	else if (check_args_no(cmd) == 3 && cmd[1][0] == '-')
	{
		if (ft_strcmp(cmd[1], "-L") && ft_strcmp(cmd[1], "-P"))
		{
			ft_putendl_fd("42sh: cd: invalid arguments.", 2);
			g_the_status = 1;
			return (1);
		}
		*i += 1;
	}
	else if (check_args_no(cmd) == 1)
	{
		cd_home(env_list);
		return (1);
	}
	return (0);
}

void			blt_cd(char **cmd, t_env **env_list)
{
	t_cd		cd;

	cd.cwd = NULL;
	cd.i = 1;
	cd.args_no = check_args_no(cmd);
	if (check_args(cmd, env_list, &cd.i) == 1)
		return ;
	if (cd.args_no == 2 || cd.args_no == 3)
	{
		ft_strcpy(cd.buff, cmd[cd.i]);
		if (cd.buff[0] != '/' && cd.buff[0] != '.' && cd.buff[0] != '-')
		{
			if (!(cd.cwd = get_cwd()))
				return ;
			ft_strcat(cd.cwd, "/");
			if (!(cd.new_path = ft_strjoin(cd.cwd, cd.buff)))
				return ;
			cd_simple(cd.new_path, env_list);
			ft_strdel_2(&cd.new_path, &cd.cwd);
		}
		else if (cmd[cd.i][0] == '-' && cmd[cd.i][1] == '\0')
			cd_back(env_list);
		else
			cd_simple(cd.buff, env_list);
	}
}

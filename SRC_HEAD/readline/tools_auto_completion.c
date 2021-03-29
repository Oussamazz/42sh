/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_auto_completion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <yabakhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 10:33:15 by yabakhar          #+#    #+#             */
/*   Updated: 2021/03/29 13:17:49 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void		ft_get_bin_dirs(t_line *line, t_affcmpl **affcmpltmp)
{
	int		flag;
	int		i;
	char	*path;
	char	**dirs;

	i = 0;
	line->compl.count = 0;
	if (!(path = get_value_expansion_path("PATH")))
		return ;
	if (!(dirs = ft_strsplit(path, ':')))
		return ;
	ft_strdel(&(path));
	line->compl.len = ft_strlen(line->compl.search);
	flag = (!line->compl.len) ? 0 : 1;
	if (line->compl.path && *line->compl.path)
		all_bin_files(line->compl.path, line, flag, affcmpltmp);
	else
	{
		while (dirs[i])
			all_bin_files(dirs[i++], line, flag, affcmpltmp);
	}
	ft_free_arr(dirs);
}

void		make_path_file(t_line *line, int command)
{
	if (ft_strchr(line->compl.str, '/'))
	{
		line->compl.search = ft_strdup(ft_strrchr(line->compl.str, '/') + 1);
		line->compl.path = ft_strsub(line->compl.str, 0,
			ft_strlen(line->compl.str) - ft_strlen(line->compl.search));
	}
	else if (!ft_strchr(line->compl.str, '/') && command)
	{
		line->compl.path = NULL;
		if (ft_strlen(line->compl.str))
		{
			if (!ft_strchr("|&;", line->compl.str[0]))
				line->compl.search = ft_strdup(line->compl.str);
			else if (ft_strchr("|&;", line->compl.str[0]))
				line->compl.search = ft_strdup(line->compl.str + 1);
		}
	}
	else if (!ft_strchr(line->compl.str, '/'))
	{
		line->compl.path = ft_strdup("./");
		line->compl.search = ft_strdup(line->compl.str);
	}
}

int			get_blen(t_affcmpl *head)
{
	int		blen;
	int		k;

	blen = 0;
	k = 0;
	while (head)
	{
		k = ft_strlen(head->content);
		blen = (blen < k) ? k : blen;
		head = head->next;
	}
	return (blen);
}

void		ft_get_all_bin_dirs(t_line *line, char **str)
{
	t_affcmpl	*affcmpl;
	t_affcmpl	*affcmpltmp;

	affcmpl = ft_memalloc(sizeof(t_affcmpl));
	affcmpltmp = affcmpl;
	ft_get_bin_dirs(line, &affcmpltmp);
	if (line->compl.count > 1)
		completion_files(affcmpl, line);
	else if (line->compl.count == 1)
		completion_str(affcmpl, line, str);
	free_list(affcmpl, affcmpltmp);
}

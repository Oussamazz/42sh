/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_comlition_file.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <yabakhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 17:24:30 by yabakhar          #+#    #+#             */
/*   Updated: 2021/03/29 17:26:15 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void		affiche_files(t_affichfile *afffile, t_affcmpl *head, t_line *line)
{
	while (head->next)
	{
		tputs(tgoto(tgetstr("cm", 0), afffile->pos_col,
			afffile->pos_row), 0, ft_output);
		ft_affiche_brackets(head->content, line);
		head = head->next;
		afffile->i++;
		if (afffile->i % afffile->col_count == 0)
		{
			afffile->pos_col = 0;
			if (head->next)
			{
				ft_putchar('\n');
				afffile->pos_row += 1;
			}
		}
		else
			afffile->pos_col += afffile->blen + 1;
	}
}

void		stock_path_file(char *str, t_line *line, t_affcmpl **affcmpl)
{
	DIR				*dir;
	struct dirent	*dent;
	int				flag;

	line->compl.len = ft_strlen(line->compl.search);
	flag = (!line->compl.len) ? 0 : 1;
	line->compl.count = 0;
	if ((dir = opendir(str)))
	{
		while ((dent = readdir(dir)) != NULL)
		{
			if ((flag && !ft_strncmp(line->compl.search, dent->d_name,
				line->compl.len)) || !flag)
			{
				(*affcmpl)->content = ft_strdup(dent->d_name);
				(*affcmpl)->next = ft_memalloc(sizeof(t_affcmpl));
				(*affcmpl) = (*affcmpl)->next;
				line->compl.count++;
			}
		}
		closedir(dir);
	}
}

void		completion_files(t_affcmpl *head, t_line *line)
{
	struct winsize	w;
	t_affichfile	afffile;

	ft_bzero(&(afffile), sizeof(t_affichfile));
	ioctl(0, TIOCGWINSZ, &w);
	afffile.pos_row = line->c_o.y + count_row(line);
	afffile.blen = get_blen(head);
	afffile.blen += (line->compl.type == 1) ? 3 : 0;
	afffile.col_count = w.ws_col / (afffile.blen + 1);
	if (afffile.col_count == 0)
		afffile.col_count++;
	ft_putchar('\n');
	affiche_files(&afffile, head, line);
	ft_putchar('\n');
	line->c_o.y = afffile.pos_row + 1;
	ft_reaffiche_prompte(line);
}

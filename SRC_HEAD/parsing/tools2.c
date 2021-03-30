/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 10:58:05 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/30 11:01:29 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				check_type_(t_type type)
{
	if (type != WORD && type != DQUOT && type != SQUOT)
		return (1);
	return (0);
}

int				setenv_exist(t_lexer *lst)
{
	while (lst)
	{
		if (!ft_strcmp(lst->data, "setenv"))
		{
			if (lst->next != NULL && lst->next->next != NULL)
			{
				if (lst->next->next->next &&
					check_type_(lst->next->next->next->type))
					return (1);
			}
		}
		lst = lst->next;
	}
	return (0);
}

char			**get_setenv_args(t_lexer *lst)
{
	char		**cmd;
	int			i;

	if (!(cmd = ft_memalloc(sizeof(char *) * 4)))
		return (NULL);
	i = 0;
	while (lst)
	{
		if (!ft_strcmp(lst->data, "setenv"))
		{
			cmd[i++] = ft_strdup(lst->data);
			if (lst->next->data)
				cmd[i++] = ft_strdup(lst->next->data);
			if (lst->next->next->data)
				cmd[i++] = ft_strdup(lst->next->next->data);
			cmd[i] = NULL;
			return (cmd);
		}
		lst = lst->next;
	}
	return (cmd);
}

void			env_update(t_lexer **tokenz, t_env **env_list)
{
	char		**cmd;

	cmd = NULL;
	if (setenv_exist(*tokenz))
	{
		if ((cmd = get_setenv_args(*tokenz)))
			blt_setenv(cmd, env_list);
		ft_free_arr(cmd);
	}
	return ;
}

char			*expansion_brackets(char *buf, t_mystruct *v)
{
	char		*data;
	char		*dollars;
	char		c;

	data = NULL;
	dollars = NULL;
	c = 0;
	if (!(data = get_the_line(buf + 1)))
		return (NULL);
	if (ft_strequ(data, "?"))
	{
		append_list(&v->tokenz, "?", WORD, &v->coord);
		ft_strdel(&data);
		return (buf + 4);
	}
	dollars = get_value_expansion(data, v->env_list);
	c = *(buf + ft_strlen(data) + 3);
	if (dollars)
		append_list(&v->tokenz, dollars, EXPANSION, &v->coord);
	buf = buf + ft_strlen(data) + 3;
	ft_strdel(&data);
	ft_strdel(&dollars);
	return (buf);
}

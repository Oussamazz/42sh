/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 10:30:32 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/30 10:33:26 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_addtmpvar(t_env **head, char *data)
{
	char	*name;
	int		i;

	name = NULL;
	i = -1;
	while (data[++i] && data[i] != '=')
		;
	name = ft_strsub(data, 0, i);
	if (!env_exist(head, name))
		addtolist(head, ft_strdup(name), ft_strdup(ft_strchr(data, '=') + 1));
	else
		modify_env(head, ft_strdup(name), ft_strdup(ft_strchr(data, '=') + 1));
	ft_strdel(&name);
}

void	ft_execenv(t_env **head, t_lexer *tokenz, int flag)
{
	t_env	*tmp;
	int		tmp_check;
	t_lexer	*head_lexer;

	(void)flag;
	tmp = *head;
	head_lexer = tokenz;
	while (tokenz && tokenz->type == ENV)
	{
		tmp_check = ft_tmpvarcheck(tokenz);
		if (tmp_check)
			ft_addtmpvar(head, tokenz->data);
		else
			ft_newvar(tokenz->data, NOT_IN_ENV);
		tokenz = tokenz->next;
		while (tokenz && tokenz->type != ENV)
			tokenz = tokenz->next;
	}
	ft_listtotab();
}

int		ft_tmpvarcheck(t_lexer *tokenz)
{
	t_lexer		*node;
	int			old_type;

	node = tokenz;
	old_type = 0;
	while (node)
	{
		if (node->type != ENV && node->type != SEP && old_type == ENV)
			return (1);
		if (node->type == SEP)
			return (0);
		old_type = node->type;
		node = node->next;
	}
	return (0);
}

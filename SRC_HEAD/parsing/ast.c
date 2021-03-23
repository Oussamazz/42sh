/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 19:09:07 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/23 18:29:46 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static t_lexer	*move_list(t_lexer *tokenz, int alltokenzsize)
{
	t_lexer *cur;

	if (!tokenz->next)
		return (NULL);
	cur = tokenz;
	while (cur != NULL && (cur->coor.node_index <= alltokenzsize))
	{
		if (cur->type != SEP && cur->type != PIPE_SYM && cur->type != AMPER && cur->type != OR && cur->type != AND)
			cur = cur->next;
		else
			break ;
	}
	if (cur && (cur->type == SEP || cur->type == PIPE_SYM || cur->type == AMPER || cur->type == OR || cur->type == AND))
		return (cur);
	return (NULL);
}

char			**fill_node(t_lexer *token, t_redir **redirections,
	t_env **env, int alltoken_size)
{
	int			i;
	char		**ret;
	size_t		ret_size;

	ret = NULL;
	if (token && env && redirections)
	{
		ret_size = get_arr_size_tokenz(token);
		if (!(ret = (char**)ft_memalloc(sizeof(char*) * (ret_size + 1))))
			return (NULL);
		i = 0;
		while (token != NULL && token->coor.node_index <= alltoken_size)
		{
			// while (token && token->type == ENV)
			// 	token = token->next;
			// if (!token)
			// 	break ;
			if (token->type == WORD || token->type == DQUOT ||
				token->type == SQUOT || token->type == EXPANSION)
				fill_cmd(ret, token, &i, env);
			else if (fill_cmd_redir(token, &i, redirections) == 1)
				break ;
			token = token->next;
			i++;
		}
		ret[i] = NULL;
	}
	return (ret);
}

static void		parse_commands_sep_pipe(t_miniast **head,
	t_lexer *tokenz, t_env **env)
{
	if (tokenz->type == PIPE_SYM && tokenz->next)
		parse_commands(&(*head)->pipe, tokenz->next, env);
	else if ((tokenz->type == SEP || tokenz->type == AMPER || tokenz->type == OR || tokenz->type == AND) && tokenz->next)
		parse_commands(&(*head)->sep, tokenz->next, env);
}

int		is_background(t_lexer *tokenz)
{
	int flag;

	flag = 0;
	while (tokenz)
	{
		if (tokenz->type == SEP)
			break ;
		if (tokenz->type == AMPER)
			flag = 1;
		tokenz = tokenz->next;	
	}
	return (flag);
}


int		is_logic_op(t_lexer *tokenz)
{
	while (tokenz)
	{
		if (tokenz->type == SEP)
			break ;
		if (tokenz->type == OR || tokenz->type == AND)
			return (tokenz->type);
		tokenz = tokenz->next;
	}
	return (0);
}
// ls -la || echo oussama

int				parse_commands(t_miniast **head, t_lexer *tokenz, t_env **env)
{
	char		**cmd;
	t_miniast	*data;
	t_redir		*redirections;
	int 		type = 0;

	cmd = NULL;
	if (!g_alltokenzsize)
		g_alltokenzsize = get_list_size(tokenz);
	while (tokenz && tokenz->coor.node_index <= g_alltokenzsize)
	{
		//ft_putendl(tokenz->data);
		redirections = NULL;
		if ((*head) == NULL && env && tokenz && tokenz->data)
		{
			if (!(data = (t_miniast*)ft_memalloc(sizeof(t_miniast))))
				return (-1);
			if (!(data->cmd = fill_node(tokenz, &(data->redirection),
				env, g_alltokenzsize)))
				return (-2);
			if (is_background(tokenz))
				data->mode |= IS_BACKGROUD;
			if ((type = is_logic_op(tokenz)))
				data->logic_op = type;
			*head = data;
		}
		else
			parse_commands_sep_pipe(head, tokenz, env);
		tokenz = move_list(tokenz, g_alltokenzsize);
	}
	g_alltokenzsize = 0;
	return (1);
}

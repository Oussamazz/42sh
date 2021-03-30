/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 10:54:11 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/30 10:56:53 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			is_background(t_lexer *tokenz)
{
	int		flag;

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

int			is_logic_op(t_lexer *tokenz)
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

int			env_skip(t_lexer **token, int *type)
{
	t_lexer	*tokenz;

	tokenz = *token;
	if ((tokenz->type == ENV) || (*type == ENV && tokenz->type == SEP))
	{
		*type = (*token)->type;
		(*token) = (*token)->next;
		return (1);
	}
	return (0);
}

size_t		get_arr_size_tokenz(t_lexer *token)
{
	size_t	size;

	size = -1;
	if (token)
	{
		size++;
		while (token != NULL)
		{
			if (token->type != PIPE_SYM &&
				token->type != METACHAR && token->type != SEP &&
					token->type != ENV)
				size++;
			else
				break ;
			token = token->next;
		}
	}
	return (size);
}

int			is_env(t_lexer **token)
{
	t_lexer *tokenz;

	tokenz = *token;
	while (tokenz)
	{
		if (tokenz->type != ENV)
			return (0);
		tokenz = tokenz->next;
	}
	return (1);
}

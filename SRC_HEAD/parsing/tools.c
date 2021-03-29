/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 15:15:23 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/29 19:16:28 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

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

void		append_(char *tmp, t_lexer **token_node, t_pointt *coord)
{
	if (ft_isalpha(tmp[0]) && ft_strchr(tmp, '=') && is_env(token_node))
		append_list(token_node, tmp, ENV, coord);
	else
		append_list(token_node, tmp, WORD, coord);
}

int			get_the_word(char *buf, t_lexer **token_node,
	t_pointt *coord, t_env **head)
{
	char	tmp[4096];
	int		j;
	int		i;
	int		size;

	j = 0;
	(void)head;
	size = ft_strlen(buf);
	i = 0;
	while (j < size && buf[j] && !ft_is_there(METACHARACTER, buf[j]) &&
		!ft_is_aggr(buf[j]) && buf[j] != '|' && buf[j] != '$' && buf[j] != '&')
	{
		if (buf[j] == '\\' && buf[j + 1])
		{
			tmp[i++] = buf[j + 1];
			j += 2;
			continue ;
		}
		tmp[i++] = buf[j++];
	}
	tmp[i] = '\0';
	buf[j] == '$' ? coord->no_space = 1 : 0;
	append_(tmp, token_node, coord);
	return (j);
}

char		*get_dollars(char *buf)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (*buf == '$')
	{
		if (count == 2)
			break ;
		buf++;
		count++;
	}
	return (ft_itoa((int)getppid()));
}

char		*and_logic_op(char *buf, t_mystruct *v)
{
	if (*(buf + 2) == '&')
	{
		ft_free_tokenz(&v->tokenz);
		ft_putendl_fd("42sh: syntax error near unexpected token `&'", 2);
		return (NULL);
	}
	append_list(&v->tokenz, "&&", AND, &v->coord);
	buf = (buf + 2);
	return (buf);
}

char		*get_splitter(char *buf, t_mystruct *v)
{
	int		position;

	position = 0;
	if (*buf == ';')
	{
		if ((position = sep_function(&v->tokenz, &v->coord)) > 0)
			return (buf + position);
		ft_free_tokenz(&v->tokenz);
		return (NULL);
	}
	else if (*buf == '&' && *(buf + 1) == '&')
		return (and_logic_op(buf, v));
	else if (*buf == '|' && *(buf + 1) == '|')
	{
		append_list(&v->tokenz, "||", OR, &v->coord);
		buf = (buf + 2);
	}
	else if (*buf == '&' && *(buf + 1) != '&' &&
		(!ft_is_there(AGG_REDI, *(buf + 1)) || !*(buf + 1)))
	{
		append_list(&v->tokenz, "&", AMPER, &v->coord);
		return (++buf);
	}
	return (buf);
}

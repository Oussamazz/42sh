/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexercore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <yabakhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 13:15:48 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/30 11:16:48 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char			*get_tild_dolar1(char *buf, t_mystruct *v)
{
	int			position;

	position = 0;
	if (*buf != '~' && (!*(buf + 1) || is_blank(*(buf + 1))))
	{
		append_list(&v->tokenz, "$", WORD, &v->coord);
		return (buf + 1);
	}
	else if (*buf == '$' && *(buf + 1) == '?' &&
			(*(buf + 2) == '\0' || ft_is_there(METACHARACTER, *(buf + 2))))
	{
		append_list(&v->tokenz, "?", WORD, &v->coord);
		return (buf + 2);
	}
	else if ((position = expansion_function(buf, &v->tokenz,
											&v->coord, v->env_list)) > 0)
		return (buf + position);
	ft_free_tokenz(&v->tokenz);
	return (NULL);
}

static char		*get_tild_dolar(char *buf, t_mystruct *v)
{
	int			position;
	char		*data;

	v->coord.no_space = 0;
	data = NULL;
	if (*buf == '$')
		ft_execenv(v->env_list, v->tokenz, EXP);
	if (*buf == '$' && *(buf + 1) && *(buf + 1) == '/' && (position = 1))
	{
		while (buf[position] && !is_blank(buf[position]) &&
			buf[position] != '$')
			position++;
		data = ft_strsub(buf, 0, position);
		append_list(&v->tokenz, data, WORD, &v->coord);
		ft_strdel(&data);
		buf++;
		while (*buf && !is_blank(*buf) && *buf != '$')
			buf++;
	}
	else if (*buf == '$' && *(buf + 1) == '{' && brackets(buf))
		return (expansion_brackets(buf, v));
	else if ((*buf == '$' || *buf == '~') && !(*buf == '$' && buf[1] == '/') &&
			(*buf != buf[1]) && !is_quote(buf[1]))
		return (get_tild_dolar1(buf, v));
	return (buf);
}

static char		*get_pipe_agr(char *buf, t_mystruct *v)
{
	int			position;

	position = 0;
	if (*buf && ft_is_there(PIPE, *buf))
	{
		append_list_pipe(&v->tokenz, ft_strdup("|"),
				PIPE_SYM, &v->coord);
		return (buf + 1);
	}
	else if (*buf && ft_is_there(AGG_REDI, *buf) && *buf != '&')
	{
		if ((position = aggr_function(buf, &v->coord, &v->tokenz)) == -1)
			return (NULL);
		return (buf + position + 1);
	}
	return (buf);
}

static char		*get_qoute_word(char *buf, t_mystruct *v)
{
	int			position;
	char		*quote;

	quote = NULL;
	if (*buf != '\\' && (is_quote(*buf) ||
		(*buf && (quote = ft_strchr_no_blanks(buf + 1, '\'', '\"')))))
	{
		position = quote_function(buf, &v->tokenz, &v->coord, quote);
		if (position < 0)
			return (NULL);
		return (buf + position);
	}
	else if ((*buf &&
			!ft_is_there(METACHARACTER, *buf)) && *buf != '$' &&
				!ft_is_there(AGG_REDI, *buf) && *buf != '|')
	{
		if (buf && *(buf))
			buf += simple_word_function(buf,
				&v->tokenz, &v->coord, v->env_list);
	}
	return (buf);
}

t_lexer			*lexer(char *buf, t_env **env_list, t_pointt *coord)
{
	t_mystruct	v;

	ft_bzero(&v, sizeof(t_mystruct));
	v.env_list = env_list;
	v.coord = *coord;
	v.size = ft_strlen(buf);
	while (*buf)
	{
		buf = ignore_blanks(buf);
		if (!buf || !*buf)
			break ;
		if ((*buf == ';' && buf[1] == ';') || (*buf == ';' && !v.tokenz))
			return ((t_lexer *)err_ret("42sh: parse error near `;'\n", NULL));
		if ((buf = get_splitter(buf, &v)) == NULL)
			return (NULL);
		if ((buf = get_tild_dolar(buf, &v)) == NULL)
			return (NULL);
		if ((buf = get_pipe_agr(buf, &v)) == NULL)
			return (NULL);
		if ((buf = get_qoute_word(buf, &v)) == NULL)
			return (NULL);
	}
	return (v.tokenz);
}

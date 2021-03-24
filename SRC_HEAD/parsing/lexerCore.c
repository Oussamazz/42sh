/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexerCore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macos <macos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 13:15:48 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/24 21:39:54 by macos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	check_type_(t_type type)
{
	if (type != WORD && type != DQUOT && type != SQUOT)
		return 1;
	return (0);
}

int			setenv_exist(t_lexer *lst)
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

char **get_setenv_args(t_lexer *lst)
{
	char **cmd;
	int i;

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

void	env_update(t_lexer **tokenz, t_env **env_list)
{
	char **cmd;

	cmd = NULL;
	if (setenv_exist(*tokenz))
	{
		if ((cmd = get_setenv_args(*tokenz)))
			blt_setenv(cmd, env_list);
		ft_free_arr(cmd);
	}
	return ;
}

// static char		*get_tild_dolar(char *buf, t_mystruct *v)
// {
// 	int			position;
// 	char		*dollars;

// 	env_update(&v->tokenz, v->env_list);
// 	if (*buf == '$' && *(buf + 1) == '$')
// 	{
// 		append_list(&v->tokenz, (dollars = get_dollars(buf)), WORD, &v->coord);
// 		ft_strdel(&dollars);
// 		return (buf + 2);
// 	}
// 	if ((*buf == '$' || *buf == '~') && !(*buf == '$'
// 		&& buf[1] == '/') && (*buf != buf[1]) && !is_quote(buf[1]))
// 	{
// 		if (*buf == '$' && (!*(buf + 1) || is_blank(*(buf + 1))))
// 		{
// 			append_list(&v->tokenz, "$", WORD, &v->coord);
// 			return (buf + 1);
// 		}
// 		else if ((position = expansion_function(buf, &v->tokenz,
// 			&v->coord, v->env_list)) > 0)
// 			return (buf + position);
// 		ft_free_tokenz(&v->tokenz);
// 		return (NULL);
// 	}
// 	return (buf);
// }

static char *get_tild_dolar(char *buf, t_mystruct *v)
{
	char c;
	int position;
	char *dollars;
	char *data = NULL;     //////biggy

	//env_update(&v->tokenz, v->env_list);
	
	v->coord.no_space = 0;
	if (*buf == '$')
		ft_execenv(v->env_list, v->tokenz, EXP);
	if(*buf == '$' &&  *(buf + 1) &&  *(buf + 1) == '/')
	{
		position = 1;
		while (buf[position] && !is_blank(buf[position]) && buf[position] != '$' )
			position++;
		data = ft_strsub(buf, 0, position);
		append_list(&v->tokenz, data, WORD, &v->coord);
		free(data);
		buf++; 
		while(*buf && !is_blank(*buf) && *buf != '$') 
			buf++;
	}
	if (*buf == '$' && *(buf + 1) == '{' && brackets(buf))
	{
		data = get_the_line(buf + 1);
		if (ft_strequ(data, "?"))
			dollars = ft_itoa(g_the_status);
		else 
			dollars = get_value_expansion(data, v->env_list);
		c = *(buf + ft_strlen(data) + 3);
		if (!is_blank(c) && c != '|')
			v->coord.no_space = 1;
		if (dollars)
			append_list(&v->tokenz, dollars, EXPANSION, &v->coord);
		buf = buf + ft_strlen(data) + 3;
		ft_strdel(&data);
		ft_strdel(&dollars);
	}
	else if (*buf == '$' && *(buf + 1) == '$')
	{
		append_list(&v->tokenz, (dollars = get_dollars(buf)), WORD, &v->coord);
		ft_strdel(&dollars);
		return (buf + 2);
	}
	else if ((*buf == '$' || *buf == '~') && !(*buf == '$' && buf[1] == '/') && (*buf != buf[1]) && !is_quote(buf[1]))
	{
		if ((!*(buf + 1) || is_blank(*(buf + 1))))
		{
			append_list(&v->tokenz, "$", WORD, &v->coord);
			return (buf + 1);
		}
		else if (*(buf + 1) == '?' && (*(buf + 2) == '\0' || ft_is_there(METACHARACTER , *(buf + 2))))
		{
			data = ft_itoa(g_the_status);
			append_list(&v->tokenz, data, WORD, &v->coord);
			ft_strdel(&data);
			return (buf + 2);
		}
		else if ((position = expansion_function(buf, &v->tokenz,
												&v->coord, v->env_list)) > 0)
			return (buf + position);
		ft_free_tokenz(&v->tokenz);
		return (NULL);
	}
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
	else if (*buf && ft_is_there(AGG_REDI, *buf))
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
	if ((*buf &&
		!ft_is_there(METACHARACTER, *buf)) && *buf != '$' &&
		!ft_is_there(AGG_REDI, *buf) && *buf != '|')
	{
		if (buf && *(buf))
			buf += simple_word_function(buf, &v->tokenz, &v->coord, v->env_list);
	}
	return (buf);
}

static char		*ignore_blanks(char *str)
{
	if (*str == '\\')
		str += 1;
	while (is_blank(*str))
		str++;
	return (str);
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
		if ((buf = get_qoute_word(buf, &v)) == NULL) // a=b echo $a	
			return (NULL);
	}
	return (v.tokenz);
}

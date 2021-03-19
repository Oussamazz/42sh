/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 15:15:23 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/19 19:17:05 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

size_t			get_arr_size_tokenz(t_lexer *token)
{
	size_t size;

	size = -1;
	if (token)
	{
		size++;
		while (token != NULL)
		{
			if (token->type != PIPE_SYM &&
				token->type != METACHAR && token->type != SEP)
				size++;
			else
				break ;
			token = token->next;
		}
	}
	return (size);
}

int				get_the_word(char *buf, t_lexer **token_node, t_pointt *coord)
{
	char	tmp[MIN_INDEX];
	int		j;
	char 	*v;
	char    *ptr;
	int 	i;
	int 	size;

	j = 0;
	size = ft_strlen(buf);
	i = 0;
	v = NULL;
	while (j < size &&  buf[j] && !ft_is_there(METACHARACTER, buf[j]) &&
		!ft_is_aggr(buf[j]) && buf[j] != '|' && buf[j] != '$' && buf[j] != '&')
	{
		if(buf[j] == '\\' && buf[j + 1])
		{
			tmp[i] = buf[j+1];
			j += 2;                ////////biggy
			i++;
			continue;
		}
		tmp[i] = buf[j];
		j++;
		i++;
	}
	if (buf[j] == '$')
		coord->no_space = 1;
	tmp[i] = '\0';
	append_list(token_node, tmp, WORD, coord);
	ft_strclr(tmp);
	return (j);
}

char			*get_dollars(char *buf)
{
	int			i;
	int			count;

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

char			*get_splitter(char *buf, t_mystruct *v)
{
	int			position;

	position = 0;
	if (*buf == ';')
	{
		if ((position = sep_function(&v->tokenz, &v->coord)) > 0)
			return (buf + position);
		ft_free_tokenz(&v->tokenz);
		return (NULL);
	}
	else if(*buf == '&' && *(buf + 1) == '&') ////////biggy
	{
		append_list(&v->tokenz, "&&", AND, &v->coord); 
		buf = (buf + 2);
	}
	else if(*buf == '|' && *(buf + 1) == '|') ////////biggy
	{
		append_list(&v->tokenz, "||", OR, &v->coord);
		buf =  (buf + 2);
	}
	else if (*buf == '&' && *(buf + 1) != '&' && (!ft_is_there(AGG_REDI, *(buf + 1)) || !*(buf + 1)))
	{
		//ft_putendl("job control"); // <= job_control_function();
		append_list(&v->tokenz, "&", AMPER, &v->coord);
		return (++buf);
	}
	return (buf);
}

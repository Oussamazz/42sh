/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 17:11:21 by afaragi           #+#    #+#             */
/*   Updated: 2021/03/27 17:34:24 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	free2dm(char ***str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		ft_strdel(&(*str)[i]);
		i++;
	}
	free((*str));
}

char		*ft_strdup_from_to(const char *s, int start, int end)
{
	int		c;
	char	*d;
	char	*rzlt;

	if (!s)
		return (NULL);
	c = 0;
	if (!(d = (char *)malloc(sizeof(char) * ((end - start) + 1))))
		return (NULL);
	while (start < end)
	{
		d[c++] = s[start++];
	}
	d[c] = '\0';
	rzlt = ft_strdup(d);
	free(d);
	if (rzlt && !rzlt[0])
		ft_strdel(&rzlt);
	return (rzlt);
}

t_alias		*check_alias_repeate(char *name, t_alias *alias)
{
	if (alias)
	{
		while (alias)
		{
			if (!(ft_strcmp(alias->name, name)))
				return (alias);
			alias = alias->next;
		}
	}
	return (NULL);
}

void		del(void *s, void *str)
{
	ft_strdel((void *)&s);
	ft_strdel((void *)&str);
}

void		ft_one_alias_del(t_alias **alst, void (*del)(void *, void *))
{
	if (alst)
	{
		del((*alst)->name, (*alst)->value);
		ft_memdel((void **)alst);
	}
}

void		free_alias_list(t_alias **alst, void (*del)(void *, void *))
{
	t_alias	*li;

	if (alst)
	{
		while (*alst)
		{
			li = (*alst)->next;
			ft_one_alias_del(&(*alst), del);
			*alst = li;
		}
	}
}


int			counter(char **str)
{
	int		i;

	i = 0;
	if (str)
	{
		while (str[i])
			i++;
	}
	return (i);
}

int			isthere_alnum(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int			checker_alias(char **str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (str)
	{
		while (str[i])
		{
			if (!isthere_alnum(str[i]))
				return (0);
			i++;
		}
	}
	return (1);
}

int			if_i_found_it(t_alias *pr, t_alias *ptr, t_alias **al, char *str)
{
	if (ft_strcmp(ptr->name, str) == 0)
	{
		if (pr)
			pr->next = ptr->next;
		else
			*al = ptr->next;
		ft_one_alias_del(&ptr, del);
		return (-1);
	}
	return (1);
}

t_alias		*alias_create(char *name, char *value)
{
	t_alias	*list;

	if (!(list = (t_alias *)(ft_memalloc(sizeof(t_alias)))))
		return (NULL);
	if (name)
	{
		list->name = ft_strdup(name);
		if (value)
			list->value = ft_strdup(value);
	}
	return (list);
}

t_alias		*alias_lst_adder(t_alias **old, t_alias *new)
{
	t_alias	*head;

	head = *old;
	if (!head)
	{
		*old = new;
		return (new);
	}
	else
	{
		while (head->next)
			head = head->next;
		head->next = new;
		new = NULL;
		return (*old);
	}
}

void		delete_alias_var(t_alias **alias, char **str)
{
	t_alias	*ptr;
	t_alias	*previous;
	int		i;

	i = 1;
	if (!str[1])
		ft_putstr_fd("unalias: Too few arguments.\n", 2);
	else
	{
		while (str[i])
		{
			ptr = *alias;
			previous = NULL;
			while (ptr && ptr->name)
			{
				if (if_i_found_it(previous, ptr, alias, str[i]) == -1)
					break ;
				previous = ptr;
				ptr = ptr->next;
			}
			i++;
		}
	}
}

void		clean_vars(t_a_v *vars, int flag)
{
	ft_strdel(&(*vars).endline);
	ft_strdel(&(*vars).startline);
	ft_strdel(&(*vars).value);
	if (flag)
		ft_strdel(&(*vars).tmp);
}

char		*return_value(char *name, t_alias *alias)
{
	if (alias)
	{
		while (alias)
		{
			if (!ft_strcmp(alias->name, name))
				return (ft_strdup(alias->value));
			alias = alias->next;
		}
	}
	return (NULL);
}

void		ft_move_replace(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		str[i] = str[i + 1];
}

t_alias		*copy_list(t_alias *alias)
{
	t_alias	*cpy;
	t_alias	*new;

	new = NULL;
	cpy = NULL;
	if (alias)
	{
		while (alias)
		{
			new = alias_create(alias->name, alias->value);
			cpy = alias_lst_adder(&cpy, new);
			alias = alias->next;
		}
	}
	return (cpy);
}

void		init_alias(t_a_v *vars, int s, int e, char **line)
{
	(*vars).start = s;
	(*vars).tmp = ft_strdup_from_to((*line), s, e);
	(*vars).ptr = (*vars).tmp;
	(*vars).tmp = ft_strtrim((*vars).tmp);
	ft_strdel(&(*vars).ptr);
}

void	get_start_end_line(t_a_v *vars, char **line, int e, t_alias **alias)
{
	(*vars).ptr = (*vars).head->name;
	(*vars).head->name = ft_strdup("#");
	ft_strdel(&(*vars).ptr);
	(*vars).value = return_value((*vars).tmp, (*alias));
	(*vars).endline = ft_strdup_from_to((*line), e, ft_strlen((*line)));
	if ((*vars).start > 0 && (*line)[(*vars).start] == ' ')
		(*vars).start++;
	(*vars).startline = ft_strdup_from_to((*line), 0, (*vars).start);
}

int			if_no_start_line(t_a_v *vars, char **line, int *s, int *e)
{
	if ((*vars).value)
	{
		(*vars).ptr = (*line);
		(*line) = ft_strjoin((*vars).value, (*line));
		ft_strdel(&(*vars).ptr);
	}
	ft_strdel(&(*vars).tmp);
	if ((*vars).catch)
	{
		(*e) = (*vars).start + ft_strlen((*vars).value);
		(*vars).tmp = ft_strdup_from_to((*line), (*vars).start, (*e));
		(*s) = (*vars).start;
		clean_vars(vars, 0);
		return (1);
	}
	ft_strdel(&(*vars).value);
	free_alias_list(&(*vars).catch, del);
	ft_strdel(&(*vars).endline);
	ft_strdel(&(*vars).startline);
	return (0);
}

int			if_there_start_line(t_a_v *vars, char **line, int *s, int *e)
{
	(*vars).ptr = (*line);
	(*line) = ft_strjoin((*vars).startline, (*vars).value);
	ft_strdel(&(*vars).ptr);
	if ((*vars).endline)
	{
		(*vars).ptr = (*line);
		(*line) = ft_strjoin((*line), (*vars).endline);
		ft_strdel(&(*vars).ptr);
	}
	if ((*vars).catch)
	{
		ft_strdel(&(*vars).tmp);
		(*e) = (*vars).start + ft_strlen((*vars).value);
		(*vars).tmp = ft_strdup_from_to((*line), (*vars).start, (*e));
		(*s) = (*vars).start;
		ft_strdel(&(*vars).value);
		ft_strdel(&(*vars).endline);
		ft_strdel(&(*vars).startline);
		return (1);
	}
	return (0);
}

void		replace_line(int *s, int e, char **line)
{
	while ((*s) < e)
	{
		ft_move_replace((*line));
		(*s)++;
	}
}

void				printfx(char **line, int s, int e, t_alias **alias)
{
	t_a_v	vars;

	init_alias(&vars, s, e, line);
	vars.catch = copy_list((*alias));
	vars.head = vars.catch;
	while (vars.tmp && (vars.head = check_alias_repeate(vars.tmp, vars.catch)))
	{
		get_start_end_line(&vars, line, e, alias);
		replace_line(&s, e, line);
		if (!vars.startline)
		{
			if (if_no_start_line(&vars, line, &s, &e))
				continue;
			else
				return ;
		}
		else if (if_there_start_line(&vars, line, &s, &e))
			continue;
		clean_vars(&vars, 1);
	}
	free_alias_list(&vars.catch, del);
	ft_strdel(&vars.tmp);
}

int			is_indice(int c)
{
	if (c == ' ' || c == '\n' || c == ';' || c == '|' || c == '&')
		return (1);
	return (0);
}

void		add_alias_list_to_file(t_alias *alias)
{
	int		file;

	file = open("/goinfre/afaragi/42sh/.biggyrc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (alias)
	{
		while (alias)
		{
			ft_putstr_fd(alias->name, file);
			ft_putstr_fd("=", file);
			ft_putendl_fd(alias->value, file);
			alias = alias->next;
		}
	}
}

void		create_alias_list()
{
	t_alias	*alias;
	int		file;
	char	*buff;
	char	**cmp;
	// char	**check;

	buff = NULL;
    cmp = NULL;
	file = open("/goinfre/afaragi/42sh/.biggyrc", O_RDONLY | O_CREAT, 0644);
	while (get_next_line(file, &buff) > 0)
	{
		// cmp = ft_strsplit(buff, '=');
		if(((counter(cmp = ft_strsplit(buff, '=')) != 2 || !checker_alias(cmp))) || !cmp)
		{
			free2dm(&cmp);
			ft_strdel(&buff);
			continue;
		}
		alias = alias_create(cmp[0], cmp[1]);
		g_alias = alias_lst_adder(&g_alias, alias);
		free2dm(&cmp);
		ft_strdel(&buff);
	}
	ft_strdel(&buff);
	close(file);
}

int			if_del_found(t_c_v *var, char **line)
{
	if ((*line)[(*var).i] == ';' || (*line)[(*var).i] == '|' ||
		!ft_strncmp(&(*line)[(*var).i], "&&", 2)
		|| !ft_strncmp(&(*line)[(*var).i], "||", 2))
	{
		if (!ft_strncmp(&(*line)[(*var).i], "&&", 2)
		|| !ft_strncmp(&(*line)[(*var).i], "||", 2))
			(*var).i += 2;
		else
			(*var).i++;
		(*var).old_i = (*var).i;
		if (!(*line)[(*var).i])
			return (1);
		while (is_blank((*line)[(*var).i]))
			(*var).i++;
		(*var).flag ^= 1;
	}
	return (0);
}

int			check_line_var(t_c_v *var, t_alias **alias, char **line)
{
	if ((is_indice((*line)[(*var).i])
	|| (!ft_strncmp(&(*line)[(*var).i], "&&", 2)
	|| !ft_strncmp(&(*line)[(*var).i], "||", 2))) && (*var).flag)
	{
		printfx(line, (*var).old_i, (*var).i, alias);
		(*var).old_i = (*var).i;
		(*var).flag = 0;
	}
	if (if_del_found(var, line))
		return (1);
	return (0);
}

void			alias_check(char **line, t_alias **alias)
{
	t_c_v	var;

	var.i = 0;
	var.old_i = var.i;
	var.flag = 1;
	var.ptr = (*line);
	(*line) = ft_strtrim((*line));
	ft_strdel(&var.ptr);
	if ((*line))
	{
		while ((*line)[var.i])
		{
			if (check_line_var(&var, alias, line))
				break ;
			var.i++;
		}
		if (var.old_i != var.i && var.flag)
			printfx(line, var.old_i, var.i, alias);
	}
}



void		add_to_alias_file(char *line, t_alias **alias)
{
	t_alias	*new;
	char	*tmp;
	char	**check;

	tmp = ft_strtrim(line);
	if (tmp && tmp[0] && tmp[0] != '=' &&
	counter(check = ft_strsplit(line, '=')) == 2 &&
	checker_alias(check) && !check_alias_repeate(check[0], (*alias)))
	{
		new = alias_create(check[0], check[1]);
		*alias = alias_lst_adder(alias, new);
	}
	else
		ft_putendl_fd("alias : Wrong Fromat Or Already added", 2);
	free2dm(&check);
    ft_strdel(&tmp);
}

void		get_value_from_list(char *line, t_alias *alias, int flag)
{
	while (alias)
	{
		if (flag)
		{
			ft_putstr_fd(alias->name, 1);
			ft_putstr_fd("='", 1);
			ft_putstr_fd(alias->value, 1);
			ft_putendl_fd("'", 1);

		}
		else if (!ft_strcmp(alias->name, line))
			ft_putendl_fd(alias->value, 1);
		alias = alias->next;
	}
	if (!flag)
		free(line);
}

void		alias_bultin(char **line, t_alias **alias)
{
	int i;

	i = 1;
	if (!line[1])
		get_value_from_list(line[0], (*alias), 1);
	if (line)
	{
		while (line[i])
		{
			if (ft_strchr(line[i], '='))
				add_to_alias_file(line[i], alias);
			else
				get_value_from_list(ft_strtrim(line[i]), (*alias), 0);
			i++;
		}
	}
}

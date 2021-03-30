/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 22:07:06 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/30 10:50:49 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void		not_is_expansion(t_expand *v, int flag)
{
	if (v->string && (!ft_is_expansion(v->arr[v->i]) || flag))
		v->string = ft_freejoin(v->string, v->arr[v->i], 0);
	if (!v->i && !v->j && (!ft_is_expansion(v->arr[v->i]) || flag))
		v->string = ft_strdup(v->arr[v->i]);
}

void			clean_it(t_c_b *check, char **str)
{
	while ((*str)[(*check).i])
	{
		if ((*str)[(*check).i] == '\\' && (*str)[(*check).i + 1])
		{
			(*check).j = (*check).i;
			while ((*str)[(*check).j])
			{
				(*str)[(*check).j] = (*str)[(*check).j + 1];
				(*check).j++;
			}
			(*check).i++;
			continue ;
		}
		(*check).i++;
	}
}

int				check_backslash(char **str)
{
	t_c_b check;

	check.j = 0;
	check.flag = 0;
	check.i = 0;
	while ((*str)[check.i])
	{
		if ((*str)[check.i] == '\\' && (*str)[check.i + 1])
			check.flag ^= 1;
		check.i++;
	}
	check.i = 0;
	check.j = 0;
	clean_it(&check, str);
	return (check.flag);
}

void			expand_checker(t_expand *v, int *flag, t_env **head)
{
	while ((*v).arr[(*v).i] != NULL
	&& (*v).j < (*v).val_size && (*v).i < (*v).val_size)
	{
		(*flag) = check_backslash(&(*v).arr[(*v).i]);
		if (!(*flag)
		&& ft_is_expansion(((*v).tmp = ft_strchr((*v).arr[(*v).i], '$'))))
			expansion_func(v, head);
		else
			not_is_expansion(v, (*flag));
		(*flag) = 0;
		(*v).i++;
	}
}

char			*expanded(t_env **head, char *str)
{
	t_expand	v;
	int			flag;

	flag = 0;
	ft_bzero(&v, sizeof(t_expand));
	if (!(v.arr = strsplit(str)))
		return (NULL);
	v.val_size = get_arr_size(v.arr) + 1;
	v.string = NULL;
	v.tmp = NULL;
	if (!(v.value = (char **)ft_memalloc(sizeof(char *) * v.val_size)))
		return (NULL);
	v.j = 0;
	v.i = 0;
	expand_checker(&v, &flag, head);
	ft_free_arr(v.arr);
	free(v.value);
	v.value = NULL;
	return (v.string);
}

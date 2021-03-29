/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:20:18 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/29 16:20:19 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	is_close(char c)
{
	if (c == ')' || c == '}' || c == ']')
		return (1);
	return (0);
}

static int	is_open(char c)
{
	if (c == '(' || c == '{' || c == '[')
		return (1);
	return (0);
}

static int	check_bracket(char a, char b)
{
	if ((a == '(' && b == ')') || (a == '{' && b == '}') ||
		(a == '[' && b == ']'))
		return (1);
	return (0);
}

int			brackets(char *str)
{
	int buffer[4096];
	int top;
	int i;

	top = 0;
	i = 0;
	while (str[i])
	{
		if (is_open(str[i]))
		{
			buffer[top++] = str[i];
		}
		if (is_close(str[i]))
		{
			if (!(check_bracket(buffer[--top], str[i])))
				return (0);
		}
		i++;
	}
	return (top == 0 ? 1 : 0);
}

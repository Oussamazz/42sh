/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_s_and_n_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 15:47:30 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/18 12:16:18 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_integer_equal(char *s1, char *s2)
{
	int		num1;
	int		num2;

	if (!ft_is_numeric(s1) || !ft_is_numeric(s2))
	{
		ft_putstr_fd("42sh: test: ", 2);
		if (!ft_is_numeric(s2))
			ft_putstr_fd(s2, 2);
		else
			ft_putstr_fd(s1, 2);
		ft_putendl_fd(": integer expression expected", 2);
		return (EXIT_FAILURE);
	}
	num1 = ft_atoi(s1);
	num2 = ft_atoi(s2);
	if (num1 == num2)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int		ft_integer_not_equal(char *s1, char *s2)
{
	int		num1;
	int		num2;

	if (!ft_is_numeric(s1) || !ft_is_numeric(s2))
	{
		ft_putstr_fd("42sh: test: ", 2);
		if (!ft_is_numeric(s1))
			ft_putstr_fd(s1, 2);
		else
			ft_putstr_fd(s2, 2);
		ft_putendl_fd(": integer expression expected", 2);
		return (EXIT_FAILURE);
	}
	num1 = ft_atoi(s1);
	num2 = ft_atoi(s2);
	if (num1 != num2)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int		ft_integer_ge(char *s1, char *s2)
{
	int		num1;
	int		num2;

	if (!ft_is_numeric(s1) || !ft_is_numeric(s2))
	{
		ft_putstr_fd("42sh: test: ", 2);
		if (!ft_is_numeric(s1))
			ft_putstr_fd(s1, 2);
		else
			ft_putstr_fd(s2, 2);
		ft_putendl_fd(": integer expression expected", 2);
		return (EXIT_FAILURE);
	}
	num1 = ft_atoi(s1);
	num2 = ft_atoi(s2);
	if (num1 >= num2)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int		ft_integer_lt(char *s1, char *s2)
{
	int		num1;
	int		num2;

	if (!ft_is_numeric(s1) || !ft_is_numeric(s2))
	{
		ft_putstr_fd("42sh: test: ", 2);
		if (!ft_is_numeric(s1))
			ft_putstr_fd(s1, 2);
		else
			ft_putstr_fd(s2, 2);
		ft_putendl_fd(": integer expression expected", 2);
		return (EXIT_FAILURE);
	}
	num1 = ft_atoi(s1);
	num2 = ft_atoi(s2);
	if (num1 < num2)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int		ft_integer_le(char *s1, char *s2)
{
	int		num1;
	int		num2;

	if (!ft_is_numeric(s1) || !ft_is_numeric(s2))
	{
		ft_putstr_fd("42sh: test: ", 2);
		if (!ft_is_numeric(s1))
			ft_putstr_fd(s1, 2);
		else
			ft_putstr_fd(s2, 2);
		ft_putendl_fd(": integer expression expected", 2);
		return (EXIT_FAILURE);
	}
	num1 = ft_atoi(s1);
	num2 = ft_atoi(s2);
	if (num1 <= num2)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

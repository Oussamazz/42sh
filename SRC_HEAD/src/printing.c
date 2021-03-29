/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 22:19:31 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/29 15:52:36 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		ft_putendl_fd_error(char *s1, char *s2, char *s3, char *s4)
{
	if (s1)
		ft_putstr_fd(s1, STDERR_FILENO);
	if (s2)
		ft_putstr_fd(s2, STDERR_FILENO);
	if (s3)
		ft_putstr_fd(s3, STDERR_FILENO);
	if (s4)
		ft_putstr_fd(s4, STDERR_FILENO);
	g_the_status = 1;
	return ;
}

void		ft_put_multistring2(char **strings)
{
	while (*strings)
		ft_putstr(*strings++);
}

void		prompt_completion(char quot)
{
	if (quot == '\"')
		ft_put_multistring2((char *[]){"\033[1;31m\"", "\033[0m",
			"\033[1;32m>", "\033[0m", 0, 0, 0});
	else
		ft_put_multistring2((char *[]){"\033[1;31m\'", "\033[0m",
			"\033[1;32m>", "\033[0m", 0, 0, 0});
	return ;
}

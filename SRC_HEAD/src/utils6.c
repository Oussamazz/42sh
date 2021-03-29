/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 22:54:08 by macos             #+#    #+#             */
/*   Updated: 2021/03/29 16:28:42 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		token_is_sep(int type)
{
	if (type == SEP || type == AND || type == OR || type == AMPER)
		return (1);
	return (0);
}

void	print_arr(char **cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i++], 1);
		write(1, " ", 1);
	}
	write(1, "\n", 1);
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 15:27:04 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/01 17:33:18 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
 
char        *ft_strjoin_cmds(char **cmd, int flag)
{
    int     i;
    char    *str;
    char    *tmp;

    i = 0;
    str = ft_strdup(cmd[i++]);
    while (cmd[i])
    {
        tmp = str;
        str = ft_strjoin(str, " ");
        ft_strdel(&tmp);
        tmp = str;
        str = ft_strjoin(str, cmd[i++]);
        ft_strdel(&tmp);
    }
    if (flag)
    {
        tmp = str;
        str = ft_strjoin(str, " | ");
        ft_strdel(&tmp);
    }
    return (str);
}

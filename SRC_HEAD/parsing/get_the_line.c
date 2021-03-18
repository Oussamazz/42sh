/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_the_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 15:51:29 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/13 17:47:48 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

// echo $(ls $(echo $HOME))

static size_t len_new_buff(const char *buf)
{
    size_t len;
    int i;
    int loop;

    len = 0;
    i = 0;
    if (buf && buf[i] == '(')
    {
        i++;
        loop = 1;
        while (buf[i] && loop)
        {
            if (buf[i] == '(')
                loop++;
            else if (buf[i] == ')')
                loop--;
            i++;
            len++;
        }
        return (len - 1);
    }
    return (-1);
}

char *get_the_line(const char *buf)
{
    size_t  size;
    char    *str;
    int i;
    int j;

    i = 0;
    size = len_new_buff(buf);
    if (!(str = ft_strnew(size)))
        return (NULL);
    if (buf[i] == '(')
        i++;
    j = 0;
    while (buf[i] && size--)
        str[j++] = buf[i++];
    return (str);
}

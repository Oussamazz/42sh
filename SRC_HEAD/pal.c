/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pal.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:51:11 by oelazzou          #+#    #+#             */
/*   Updated: 2021/02/24 09:50:56 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"


void    putstr_(char *str, int start, int len)
{
    while (str[start] && start < len)
        ft_putchar(str[start++]);
}

int main(int ac, char *av[])
{
    int L;
    int R;
    int start = 0;
    int maxlen = 0;
    int k;
    int flag;
    int len = ft_strlen(av[1]);
    if (ac == 2)
    {
        L = 0;
        while (L < len)
        {
            R = L;
            while (R < len)
            {
                flag = 1;
                k = 0;
                while (k < (R - L + 1) / 2)
                {
                    if (av[1][L + k] != av[1][R - k])
                        flag = 0;
                    k++;
                }
                if (flag && (R - L + 1) >= maxlen)
                {
                    start = L;
                    maxlen = R - L + 1;
                }
                R++;
            }
            L++;
        }
        putstr_(av[1], start, start + maxlen);
    }
    ft_putchar('\n');
    return (0);
}

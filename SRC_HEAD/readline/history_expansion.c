/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 20:16:12 by yabakhar          #+#    #+#             */
/*   Updated: 2020/11/29 20:16:15 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

char *get_node(char *str)
{
    t_node *history;
    history = add_to_history(NULL);
    int nuber = ft_atoi(str);
    int calc = calc_list(history);
    if (nuber < 0)
       nuber = calc - ft_abs(nuber);
    if (ft_abs(nuber) > calc)
    {
        ft_putstr("bash: !");
        ft_putstr(str);
        ft_putendl(": event not found");
        return (NULL);
    }
    return (get_content_in_list(nuber));
}

char		*ft_k_strjoin(char *s1, char *s2)
{
	char	*str;
    char    *ptr;
    ptr = ft_strjoin(s1," ");
	str = ft_strjoin(ptr, s2);
	free(s1);
    free(ptr);
	return (str);
}

char		*ft_freejoin(char *s1, char *s2, int num)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (num == 0)
        free(s1);
    else if (num == 1)
        free(s2);
    else if (num == 2)
    {
        free(s1);
        free(s2);
    }
	return (str);
}

char *mm(int i)
{
    int k = i;
    char *pp = get_node("-1");
    char *kk;
    while (i > 0)
    {
        if (k == i)
            kk = ft_strjoin(pp,"");
        else
            kk = ft_freejoin(kk,pp,0);
        i--;
    }
    return (kk);
}


char  *dwdwed(char *rr)
{
    int index = 0;
    if (index2_fc(rr,&index))
        return (get_content_in_list(index));
    else
    {
        ft_putstr("bash: !");
        ft_putstr(rr);
        ft_putendl(": event not found");
    }
    return NULL;
}

char *ft_hellos(char *rr,char *str)
{
    int i = 0;

    if (!(ft_strncmp(rr,"!",1)))
    {
        while (str[i] == '!')
            i++;
        char *jj = ft_strsub(rr,i - 1,ft_strlen(str) - i);
        char *ptr;
        if (i % 2 == 0)
        {
            i = i / 2;
            ptr = mm(i);
            ptr = ft_freejoin(ptr,jj,2);
            return ptr;
        }
        else
        {
            i--;
            i = i / 2;
            ptr = mm(i);
            ptr = ft_k_strjoin(ptr,"!");
            if (!dwdwed(jj))
            {
                free(ptr);
                return NULL;
            }
            ptr = ft_freejoin(ptr,jj,2);
            return (ptr);
        }
    }
    else if (ft_isnumber(rr) || ((rr[0] == '-') && (ft_isnumber(rr + 1))))
        return (get_node(rr));
    else
        return(dwdwed(rr));
}

char  *ft_putstr_debut_fin(char *str,int debut,int fin)
{   
    int i;

    i = 0;
    char *rest;
    int len = 0;
    while (str[i])
    {
        if (i >= debut)
            len++;
        if (i == fin)
            break;
        i++;
    }
    rest = ft_strsub(str,debut,len);
    if (ft_hellos(rest + 1,rest) != NULL)
        return(ft_hellos(rest + 1,rest));
    return NULL;
}

void history_expansion(char *str)
{
    int i;
    int j;
 
    i = 0;
    j = 0;
    char *hold = ft_strdup("");
    char *tmp;
    while (str[i])
	{
        i++;
		if (str[i] == '!')
            while (str[i] && str[i] == '!')
                i++;
        if (str[i] != '!')
        {
        	while (str[i] && str[i] != '!')
             	i++;
            tmp = ft_putstr_debut_fin(str, j, i - 1);
        	if (tmp)
            {
                if (j == 0)
                    hold = ft_freejoin(tmp, hold, 2);
                else
                    hold = ft_freejoin(hold, tmp, 2);
            }
            else
                break;
       	}
        j = i;
	}
    if (tmp != NULL)
        ft_putendl(hold);
    ft_strdel(&(hold));
}

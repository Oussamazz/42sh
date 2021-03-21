/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 17:11:21 by afaragi           #+#    #+#             */
/*   Updated: 2021/03/21 18:46:20 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void free2Dm(char ***str)
{
    int i;
    i = 0;
    while ((*str)[i])
    {
        ft_strdel(&(*str)[i]);
        i++;
    }
    free((*str));
}

static int word_count(char *s, char c)
{
    int i;
    int q;
    int res;

    i = 0;
    res = 0;
    q = 0;
    while (s[i] != '\0')
    {
        if (s[i] == '\'')
            q ^= 1;
        if (s[i] != c && s[i + 1] == c && !q)
            res++;
        i++;
    }
    if (s[i] == '\0' && s[i - 1] != c)
        res++;
    return (res);
}

static int word_len(char *s, char c)
{
    int len;
    int q;

    len = 0;
    q = 0;
    while (*s != '\0')
    {
        if (*s == c && !q)
            break;
        if (*s == '\'')
            q ^= 1;
        len++;
        s++;
    }
    return (len);
}

char **splite_quote_v(char const *s, char c)
{
    int word_countx;
    char **str;
    int i;

    if (!s || !*s)
        return (NULL);
    word_countx = word_count((char *)s, c);
    if (!(str = (char **)ft_memalloc(sizeof(char *) * word_countx + 1)))
        return (NULL);
    i = 0;
    if (!str)
        return (str);
    while (word_countx-- && *s)
    {
        while (*s == c && *s != '\0')
            s++;
        if (!(str[i] = ft_strsub((char *)s, 0, word_len((char *)s, c))))
            return (str);
        if (!str[i])
            return (str);
        s = s + word_len((char *)s, c);
        i++;
    }
    str[i] = NULL;
    return (str);
}

int check_alias_repeate(char *line)
{
    int file;
    char *buff;
    char **cmp;
    char **cmp2;

   file = open(".biggyrc", O_RDONLY);
   while(get_next_line(file, &buff) > 0)
   {
       cmp = ft_strsplit(buff, '=');
       cmp2 = ft_strsplit(line, '=');
       if(!ft_strcmp(cmp[0], cmp2[0]))
        return(0);
       ft_strdel(&buff);
       free2Dm(&cmp);
       free2Dm(&cmp2);
   }
   free(line);
   close(file);
   return(1);
}

void add_to_alias_file(char *line)
{
    int file;
    char *tmp;

    file = open(".biggyrc", O_WRONLY | O_CREAT | O_APPEND, 0644);
    tmp = ft_strtrim(line);
    if (tmp && tmp[0] && tmp[0] != '=' && check_alias_repeate(ft_strtrim(line)))
    {
        ft_putendl_fd(line, file);
        ft_strdel(&tmp);
    }
    else
        ft_putendl_fd("alias : Wrong Fromat Or Already added", 2);
    close(file);
}



void get_value_from_file(char *line, int flag)
{
   int file;
   char *buff;
   char **cmp;

   file = open(".biggyrc", O_RDONLY);
   while(get_next_line(file, &buff) > 0)
   {
       cmp = ft_strsplit(buff, '=');
       if(!ft_strcmp(cmp[0], line) || flag)
        puts(buff);
       ft_strdel(&buff);
       free2Dm(&cmp);
   }
   if(!flag)
    free(line);
   close(file);
}

void alias_bultin(char **line)
{
    int i;

    i = 1;
    if(!line[1])
         get_value_from_file("Getall", 1);
    if (line)
    {
        while (line[i])
        {
            if (ft_strchr(line[i], '='))
                add_to_alias_file(line[i]);
            else
                get_value_from_file(ft_strtrim(line[i]), 0);
            i++;
        }
    }
}

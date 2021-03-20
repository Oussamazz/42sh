/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_l.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 00:09:39 by yabakhar          #+#    #+#             */
/*   Updated: 2020/10/19 17:35:42 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int ft_abs(int num)
{
    return (num = (num >= 0) ? num : (num * -1));
}

void get_index_in_list(t_node **history,int debut)
{
	int i = 0;
	while (*history)
	{
		if (i == debut)
			return ;
		(*history) = (*history)->next;
		i++;
	}
	return ;
}

char *get_content_in_list(int debut)
{
	int i;
    t_node *history;

    i = 0;
    history = add_to_history(NULL);
	while (history)
	{
		if (i == debut)
			return(history->content);
		(history) = (history)->next;
		i++;
	}
	return(NULL);
}

int calc_list(t_node *history)
{
	int i = 0;
	while (history)
	{
		i++;
		history = history->next;
	}
	return (i);
}
int ft_sin(int i)
{
    if (i >= 0)
        return(-1);
    return(1);
}

void ft_affiche_tab_l(char **result,int size,t_opt *opt,int sin)
{
    int k;

    k = 0;
    if (opt->r)
    {
        while (size)
        {
            if (!opt->n)
                ft_putnbr(opt->fin);
            ft_putchar('\t');
            ft_putendl(result[--size]);
            opt->fin = opt->fin - sin;  
        }
    }
    else if (!opt->r)
    {
        while (size > k)
        {
            if (!opt->n)
                ft_putnbr(opt->debut);
            ft_putchar('\t');
            ft_putendl(result[k++]);
            opt->debut = opt->debut + sin;
        }
    }
}

void ft_calc_debut_fin(t_opt *opt)
{
    opt->debut = ((ft_abs(opt->debut) > opt->sizeoflist) || (opt->debut == 0)) ? (-1) : opt->debut;
    opt->fin = ((ft_abs(opt->fin) > opt->sizeoflist) || (opt->fin == 0)) ? (-1) : opt->fin;
    opt->debut = (opt->debut < 0) ? (opt->sizeoflist - ft_abs(opt->debut)) : opt->debut;
    opt->fin = (opt->fin < 0) ? (opt->sizeoflist - ft_abs(opt->fin)) : opt->fin;
}

int    ft_get_debut_fin(t_opt *opt,char **hold)
{
    if (opt->count >= 1)
    {
		if (!(get_index_fc(hold[opt->check],&opt->debut)))
			return 0;
        if (opt->count > 1)
            if (!(get_index_fc(hold[opt->check + 1],&opt->fin)))
                return 0;
        return (1);
    }
    return (0);
}

int ft_get_debut_fin_l(t_opt *opt,char **hold)
{
    if (opt->count == 0)
    {
        opt->debut = -16;
        opt->fin = 0;
    }
    else
    {
	    if (!ft_get_debut_fin(opt,hold))
            return (0);
    }
    ft_calc_debut_fin(opt);
    return(1);
}

void ft_calc_range_of_debut_fin(t_opt *opt,int *size,char ***result)
{
    t_node *history;
    int i;

    i = 0;
    history = add_to_history(NULL);
    *size = opt->debut - opt->fin;
    *size += (((*size > 0) ? 1 : -1) * (opt->count >= 0));
    get_index_in_list(&history,opt->debut);
    (*result) = ft_memalloc(sizeof(char *) * (ft_abs(*size) + 1));
    while(1)
    {
        (*result)[ft_abs(i)] = history->content;
        history = (*size > 0) ? history->prev : history->next;
        i += (*size > 0) ? 1 : -1;
        if (!history || i == *size)
            break ;
    }
}

int fc_l(t_opt *opt,char **hold)
{
    char **result;
    int size;

    if (ft_get_debut_fin_l(opt,hold))
    {
        ft_calc_range_of_debut_fin(opt,&size,&result);
        ft_affiche_tab_l(result,ft_abs(size),opt,ft_sin(size));
        free(result);
    }
    return (0);
}
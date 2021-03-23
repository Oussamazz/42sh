/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 17:13:38 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/23 14:29:58 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void		init_coord(t_pointt *cor)
{
	if (cor)
	{
		cor->node_index = 0;
		cor->node_addr = 0;
		cor->no_space = 0;
		cor->aggr_index = 1;
		cor->pipe_index = 1;
	}
	return ;
}

int				main(int ac, char **av, char **env)
{
	t_env		*env_list;
	time_t		now;

	env_list = NULL;
	ft_envvinit(env);
	g_parproc = getpid();
	stock_env(env, &env_list);
	time(&now);
	if (ac > 1 && env_list)
		flag_g(av, &env_list, &now);
	if (!(g_tty_name = ttyname(0)))
		return (1);
	source_sh(&env_list);
	env_list = NULL;
	if (g_tty_name)
		free(g_tty_name);
	return (0);
}

static void		assign_v(t_getfullcmd *v)
{
	v->quote_opened ^= 1;
	v->flag = v->quote_opened;
	v->c = v->tmp[v->i] * v->quote_opened;
}

char			*get_full_cmd(void)
{
	t_getfullcmd v;
	int len = 0;
	char *tmp = 0;
	ft_bzero(&v, sizeof(t_getfullcmd));
	v.cmd = ft_strdup("");
	while (v.cmd && (v.tmp = ft_readline(v.flag)))
	{
		v.i = 0;
		len = ft_strlen(v.tmp);
		while (v.i < len && v.tmp[v.i])
		{
			if(v.tmp[v.i] == '\\' && (v.tmp[v.i + 1] && (v.tmp[v.i + 1] == '\'' || v.tmp[v.i + 1] == '\"' || v.tmp[v.i + 1] == '\\')))      ////////biggy
			{
				v.i += 2;
				if(v.i >= len)
					break;
				continue;
			}
			if ((v.tmp[v.i] == '\\' && !v.tmp[v.i + 1]))
			{
				tmp = ft_readline(1);
				v.tmp = ft_strjoin(v.tmp , tmp);      ////////biggy
				len += ft_strlen(tmp);
				if(!ft_strlen(tmp))
				{
					free(tmp);
					break;
				}
				free(tmp);
				continue;
			}
			if (is_quote(v.tmp[v.i]) && (v.c == v.tmp[v.i] || v.c == 0))
				assign_v(&v);
			v.i++;
		}
		v.cmd = ft_freejoin(v.cmd, v.tmp, 2);
		if (!v.quote_opened)
			break ;
		if (g_clt_d || g_clt_c)
			return (handel_signal(&v));
		prompt_completion(v.c);
		// ft_putnbr(v.flag);
		v.cmd = ft_freejoin(v.cmd, "\n", 0);
	}
	return (v.tmp ? v.cmd : NULL);
}

static void print_tokenz(t_lexer *tokenz)
{
	while (tokenz)
	{
		ft_putnbr(tokenz->type);
		ft_putstr("=> ");
		ft_putstr(tokenz->data);
		ft_putendl("%");
		tokenz = tokenz->next;
	}
	return ;
}

void			source_sh(t_env **head)
{
	t_mystruct	v;

	g_his = NULL;
	signal(SIGCHLD, checkchild2);
	signal(SIGTSTP, SIG_IGN);
	ft_bzero(&v, sizeof(t_mystruct));
	v.status[0] = 1;
	g_hashtable = ht_create();
	while (v.status[0])
	{
		ft_putstr("status: ");
		ft_putnbr(g_the_status);
		ft_putchar('\n');
		init_coord(&v.coord);
		ft_prompte();
		if (!(v.str = get_full_cmd()))
			continue ;
		ft_envcpy(head); 
		if (*(v.str) && !(v.tokenz = lexer(v.str, head, &v.coord)))
			g_the_status = 258;
		print_tokenz(v.tokenz);
		ft_execenv(head, v.tokenz);
		ft_putendl_fd("_______________________", 1);
		v.status[1] = check_grammar_tokenz(v.tokenz);
		if (v.tokenz && head && v.status[1] > 0)
			v.status[1] = parse_commands(&v.ast, v.tokenz, head);
		// ft_putendl("tree:");
		print_btree(v.ast);
		ft_putendl_fd("_______________________", 1);
		if (v.str[0] != '\0' && !str_is_blank(v.str))
			add_to_history(v.str);
		if (v.status[1] > 0 && v.ast && head && v.ast->cmd)
			v.status[0] = execute(v.ast, head);
		free_vars(&v, (int[]){F_TMP, F_TOKENZ, F_AST, F_STR, F_G_HIS}, 5);
	}
}

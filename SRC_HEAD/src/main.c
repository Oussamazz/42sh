/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 17:13:38 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/30 11:06:41 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int					main(int ac, char **av, char **env)
{
	t_env			*env_list;

	(void)ac;
	(void)av;
	env_list = NULL;
	ft_envvinit(env);
	create_alias_list();
	stock_env(env, &env_list);
	stock_env(env, &g_head);
	if (!(g_tty_name = ttyname(0)))
		return (1);
	source_sh(&env_list);
	env_list = NULL;
	if (g_tty_name)
		free(g_tty_name);
	return (0);
}

char				*get_full_cmd(void)
{
	t_getfullcmd	v;
	int				len;
	char			*tmp;

	len = 0;
	tmp = NULL;
	ft_bzero(&v, sizeof(t_getfullcmd));
	v.cmd = ft_strdup("");
	while (v.cmd && (v.tmp = ft_readline(v.flag)))
	{
		v.i = 0;
		len = ft_strlen(v.tmp);
		backslash_checker(&v, &len, &tmp);
		v.cmd = ft_freejoin(v.cmd, v.tmp, 2);
		if (!v.quote_opened)
			break ;
		if (g_clt_d || g_clt_c)
			return (handel_signal(&v));
		prompt_completion(v.c);
		v.cmd = ft_freejoin(v.cmd, "\n", 0);
	}
	return (v.tmp ? v.cmd : NULL);
}

void				ft_fixenv(t_lexer **token)
{
	t_lexer			*tokenz;

	tokenz = *token;
	while (tokenz)
	{
		if (token_is_sep(tokenz->type) && tokenz->next)
		{
			tokenz = tokenz->next;
			while (tokenz && tokenz->type == WORD &&
				ft_strchr(tokenz->data, '='))
			{
				tokenz->type = ENV;
				tokenz = tokenz->next;
			}
		}
		else if (tokenz)
			tokenz = tokenz->next;
	}
}

void				init_(t_mystruct *v)
{
	signal(SIGCHLD, checkchild2);
	signal(SIGTSTP, SIG_IGN);
	ft_bzero(v, sizeof(t_mystruct));
	g_hashtable = ht_create();
}

void				source_sh(t_env **head)
{
	t_mystruct		v;

	init_(&v);
	while (1)
	{
		init_coord(&v.coord);
		ft_prompte();
		if (!(v.str = get_full_cmd()))
			continue ;
		alias_check(&v.str, &g_alias);
		ft_envcpy(head);
		if (*(v.str) && !(v.tokenz = lexer(v.str, head, &v.coord)))
			g_the_status = 258;
		v.status[1] = check_grammar_tokenz(v.tokenz);
		ft_fixenv(&v.tokenz);
		ft_execenv(head, v.tokenz, NOT_EXP);
		if (v.tokenz && head && v.status[1] > 0)
			v.status[1] = parse_commands(&v.ast, v.tokenz, head);
		if (v.str[0] != '\0' && !str_is_blank(v.str))
			add_to_history(v.str);
		if (v.status[1] > 0 && v.ast && head && v.ast->cmd)
			v.status[0] = execute(v.ast, head);
		free_vars(&v, (int[]){F_TMP, F_TOKENZ, F_AST, F_STR, F_G_HIS}, 5);
	}
}

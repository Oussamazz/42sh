/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_fc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 16:35:28 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/29 16:44:24 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		execute_fc(char *line)
{
	int			status;
	t_miniast	*ast;
	t_lexer		*lex;
	t_pointt	coor;

	ast = NULL;
	init_coord(&coor);
	status = 0;
	if (!(lex = lexer(line, &g_head, &coor)))
		return ;
	ft_fixenv(&lex);
	ft_execenv(&g_head, lex, NOT_EXP);
	if (lex)
		status = parse_commands(&ast, lex, &g_head);
	if (status && ast && g_head && ast->cmd)
		execute(ast, &g_head);
	ft_free_tokenz(&lex);
	ft_free_tree(&ast);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_fc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 16:35:28 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/25 18:56:10 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void    execute_fc(char *line)
{
    int status;
    t_miniast *ast = NULL;
    t_lexer *lex;
    t_pointt coor;
    int pid = 0;

    init_coord(&coor);
    ft_putendl("execution0");
    ft_putendl(line);
    status = 0;
    lex = lexer(line, &g_head, &coor);
    if (lex && (status =check_grammar_tokenz(lex)))
    ft_fixenv(&lex);
    ft_execenv(&g_head, lex, NOT_EXP);
    print_tokenz(lex);
    if (lex && g_head && status)
		status = parse_commands(&ast, lex, &g_head);
    ft_putendl("--------");
    if (ast)
        print_btree(ast);
    ft_putendl("--------");
    if (status > 0 && ast && g_head && ast->cmd)
    {

        ft_putendl("execution");
            execute(ast, &g_head);
            waitpid(pid, 0, 0);
    }
    ft_free_tokenz(&lex);
    ft_free_tree(&ast);
}
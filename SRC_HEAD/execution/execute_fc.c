/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_fc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macos <macos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 16:35:28 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/26 22:31:05 by macos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
// str = "vim "

void execute_fc(char *line)
{
    int status;
    t_miniast *ast = NULL;
    t_lexer *lex;
    t_pointt coor;

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
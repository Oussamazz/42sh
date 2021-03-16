/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 17:49:47 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/16 14:45:52 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"


// echo $(ls $(echo $HOME))


// void        execute_sub(t_miniast *ast, t_lexer **tokenz, t_env **env_list)
// {
    
// }


void    sub_shell_exec(char *line, t_lexer **tokenz, t_env **env_list)
{
    t_mystruct v;

    ft_bzero(&v, sizeof(t_mystruct));
    if (line)
    {
        v.tokenz = lexer(line, env_list, &v.coord);   
        if (v.tokenz && check_grammar_tokenz(v.tokenz))
            parse_commands(&v.ast, v.tokenz, env_list);
        if (v.ast)
        {
            //execute_sub(v.ast, tokenz, env_list); // append output of the execution (splited by '\n') to tokenz
            ft_putstr_fd("to be executed: ", 1);
            print_btree(v.ast);
        }
        // if (v.ast && v.ast->cmd)
    }
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_blt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 18:51:39 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/23 15:35:58 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	exit_blt(t_miniast **root, t_lexer **lex,
	t_env **env_list, char **buff)
{
	ft_putendl("exit");
	ft_free_history();
	// if (lex)
	// 	ft_free_tokenz(lex);
	// if (root)
	// 	ft_free_tree(root);
	// if (env_list)
	// 	free_env_list(env_list);
	// if (buff)
	// 	ft_strdel(buff);
	ft_tabfree();
	ft_listfree();
	ft_free_his(&g_his);
}

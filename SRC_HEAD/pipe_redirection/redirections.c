/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 17:41:00 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/17 18:42:27 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

size_t			redirerction_parse(t_lexer **token_node, char **agg,
	t_pointt *cor)
{
	int			j;

	j = 0;
	while (agg[j] != NULL && agg[j][0] != '\0')
	{
		if (ft_isdigit(agg[j][0]) && j == 0)
			append_list_redi(token_node, ft_strdup(agg[j]), L_REDIR, cor);
		else if (ft_is_there(AGG_REDI, agg[j][0]))
			append_list_redi(token_node, ft_strdup(agg[j]), AGGR_SYM, cor);
		else if (ft_isascii(agg[j][0]))
			append_list_redi(token_node, ft_strdup(agg[j]), R_REDIR, cor);
		j++;
	}
	ft_free_arr(agg);
	return (g_agg_len);
}

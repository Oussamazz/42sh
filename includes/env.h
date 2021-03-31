/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <yabakhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:48:56 by ahmcherk          #+#    #+#             */
/*   Updated: 2021/03/30 12:44:28 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# define IN_ENV 1
# define NOT_IN_ENV 0
# define DELL 0
# define SEARCH 1
# include "libft.h"

char					**g_envtab;
char					**g_settab;
typedef struct			s_envv
{
	char				*name;
	char				*content;
	char				*all;
	int					type;
	struct s_envv		*next;
}						t_envv;

t_envv					*g_set;
int						ft_dblstrlen(char **str);
char					**ft_strdbldup(char **str);
void					ft_strdbldel(char ***str);
void					ft_putdblstr(char **str);
t_envv					*ft_setnewnode(void);
void					ft_setaddnode(char *name, char *content, char *all,
	int type);
void					ft_setdelnode(t_envv **node, t_envv **prev, int count);
void					ft_listtotab(void);
void					ft_tabfree(void);
t_envv					*ft_varchr(char *str, int flag);
void					ft_newvar(char *str, int type);
void					ft_modvar(t_envv **node, char *str);
void					ft_envvinit(char **env);
void					ft_tabfree(void);
void					ft_listfree(void);
void					ft_export(char **ta);

#endif

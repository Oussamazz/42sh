/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <yabakhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 12:55:33 by yabakhar          #+#    #+#             */
/*   Updated: 2021/03/29 18:41:05 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H
# include <stdio.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>
# include <sys/ioctl.h>

# define UP 4283163
# define DOWN 4348699
# define LEFT 4479771
# define RIGHT 4414235
# define SPACE 32
# define DEL 127
# define END 10
# define ESC 27
# define ALT_RTH 1130044187
# define ALT_LFT 1146821403
# define HOME 4741915
# define DEEP 4610843
# define PAGE_DOWN 1113266971
# define PAGE_UP 1096489755
# define ALT_D 4
# define ALT_S 40899
# define ALT_V 10127586
# define TRUE 1
# define ALT_C 42947
# define CTRL_L 12
# define CTRL_R 18
# define TAB 9
# define PATH_HISTORY_FILE "./.42sh_history"
# define PATH_FC_FILE "./.fc-42sh"

typedef struct		s_opt
{
	int				l;
	int				n;
	int				s;
	int				e;
	int				r;
	int				i;
	char			*editeur;
	int				check;
	int				sizeoflist;
	int				fin;
	int				count;
	int				debut;
}					t_opt;

typedef struct		s_node
{
	char			*content;
	int				content_len;
	char			*tmp;
	int				len;
	struct s_node	*next;
	struct s_node	*prev;
}					t_node;

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct		s_expansion_h
{
	int				i;
	int				j;
	char			*hold;
	char			*tmp;
}					t_expansion_h;

typedef struct		s_affcmpl
{
	char				*content;
	struct s_affcmpl	*next;
}					t_affcmpl;

typedef struct		s_cmplt
{
	int				prefix_pos;
	int				len;
	int				bracket;
	int				type;
	char			*path;
	char			*str;
	char			*search;
	int				count;
}					t_cmplt;

typedef struct		s_affichfile
{
	int				pos_row;
	int				blen;
	int				col_count;
	int				pos_col;
	int				i;
}					t_affichfile;

typedef struct		s_mode_r
{
	int				flag;
	char			*s;
	char			c[2];
	char			tmp;
	int				x;
	int				y;
	int				count;
}					t_mode_r;

typedef struct		s_line
{
	t_point			c_o;
	t_point			c_v;
	t_mode_r		mode_r;
	t_cmplt			compl;
	int				col;
	int				row;
	int				len;
	int				index;
	int				i;
	int				cursor;
	int				*tabl;
	int				c_len;
	int				b_line;
	int				slct;
	int				slctd;
	int				slctf;
	char			*sltstr;
	int				r;
	char			c[2];
}					t_line;

t_line *g_line;
char *g_str;
int g_clt_c;
int g_clt_d;
int g_lohtory;

/*
** readline function
*/

char				*ft_readline(int flag);
void				ft_stock(char *str, t_node **list, t_line *line);
void				cur_goto(t_line *line, int cursor);
void				ft_alt_rth(char *str, t_line *line);
void				ft_alt_lft(char *str, t_line *line);
void				ft_printnbl(char **str, t_line *line, char c);
void				ft_delet(char **str, t_line *line);
void				ft_next(t_node **head, t_node **list, char **str,
	t_line *line);
void				ft_prev(t_node **head, t_node **list, char **str,
	t_line *line);
void				get_cursor_position(t_line *line);
char				*ft_end(t_node **current, t_line *line);
void				print_prompte(t_line *line);
void				move_left(t_line *line, char *str);
void				move_right(t_line *line, char *str);
void				home_deep(t_line *line, char *str);
void				esc(void);
void				esc1(void);
void				ft_init(t_line *line, t_node **current);
void				ft_multilne(char *str, t_line *line);
void				move_up(t_line *line);
void				move_down(t_line *line);
void				move_cursor_v(t_line *line);
void				ft_update_cursor_o(t_line *line);
void				print_line(char *str);
void				ft_select(t_line *line, char *str);
void				ft_unselect(t_line *line, char *str);
void				ft_chack_selction(t_line *line, char *str);
void				ft_print_print(char **str, t_line *line, char *buff);
void				ft_unselect(t_line *line, char *str);
void				ft_clear(t_line *line, char *str);
void				ft_copie(t_line *line, char *str);
void				ft_prompte(void);
void				ft_history_goto(t_node **current, t_node *new,
	t_line *line);
char				*ft_end(t_node **current, t_line *line);
void				free_history_node(t_node *node);
void				ft_unset_terminal(void);
void				ft_put_multistring(char **strings);
void				ft_free_history(void);
void				ft_signale(void);
void				ft_ctl_l(t_line *line, char *str);
void				ft_ctl_d(int flag);
int					ft_output(int str);
int					count_len(t_line *line);
int					count_row(t_line *line);
int					ft_readline_builtines(int flag, char *buff,
	t_line *line, t_node **current);
t_node				*add_to_history(const char *str);
void				prompte_mode_r(char c, char **str);
void				mode_r(t_line *line);
void				delet_mode_r(char **str, t_line *line);
int					get_index_mode_r(t_line *line, int *index);
void				print_prompte_(t_line *line, int error);
void				search_mode_r(t_line *line, t_node **current);
void				ft_disable_mode_r(t_line *line);
void				ft_auto_completion(t_line *line, char **str);
void				completion_files(t_affcmpl *head, t_line *line);
void				ft_d(t_line *line);
void				completion_str(t_affcmpl *head, t_line *line, char **str);

/*
** fc function
*/

void				opt_error(char c);
int					ft_isnumber(char *str);
int					check_index_fc(char *str, int *index);
int					check_isnbrvalide(char *str);
int					index2_fc(char *str, int *index);
int					get_index_fc(char *hold, int *index);
int					preparer_path(char *editeur, t_opt *opt);
int					check_debut_fin_e(t_opt *opt, char **hold);
void				count_arg_fc(t_opt *opt);
int					check_opt(t_opt *opt, char *hold);
void				execute_commande_fc(const char *file);
void				fc_without_flag(t_opt *opt, char **hold);
void				ft_handel_fc(t_opt *opt, char **hold);
void				parce_param_fc(char **hold);
int					ft_abs(int num);
void				get_index_in_list(t_node **history, int debut);
char				*get_content_in_list(int debut);
int					calc_list(t_node *history);
int					ft_sin(int i);
void				ft_affiche_tab_l(char **result, int size, t_opt *opt,
	int sin);
void				ft_calc_debut_fin(t_opt *opt);
int					ft_get_debut_fin(t_opt *opt, char **hold);
int					ft_get_debut_fin_l(t_opt *opt, char **hold);
void				ft_calc_range_of_debut_fin(t_opt *opt, int *size,
	char ***result);
int					fc_l(t_opt *opt, char **hold);
void				ft_affiche_tab_e(char **result, int size, t_opt *opt,
	int sin);
int					fc_e(t_opt *opt, char **hold);
int					ft_calc(char **hold);
void				load_hsitory(char const *str);
void				print_in_history(const char *file);
void				execute_open_file(char *editeur);
char				*history_expansion(char *str);
void				ft_get_all_bin_dirs(t_line *line, char **str);
void				all_bin_files(char *str, t_line *line, int flag,
	t_affcmpl **affcmpl);
int					get_blen(t_affcmpl *head);
void				make_path_file(t_line *line, int command);
void				ft_free_list(t_affcmpl **affcmpl);
void				ft_reaffiche_prompte(t_line *line);
void				ft_builtine_parameter_file(t_line *line, char **str);
void				make_path_parameters(t_line *line);
void				stock_path_paramters(t_line *line, t_affcmpl **affcmpl);
void				stock_path_file(char *str, t_line *line,
	t_affcmpl **affcmpl);
void				fc_many_argement(t_opt *opt);
void				fc_one_argement(int fd, t_opt *opt);
void				ft_handel_fc(t_opt *opt, char **hold);
void				fc_s(t_opt *opt, char **hold);
void				free_list(t_affcmpl *affcmpl, t_affcmpl *affcmpltmp);
int					is_in_str(char c, const char *cmp);
char				*ft_strrsearch(char *s, const char *cmp, size_t size);
char				*ft_strrsearch2(char *s, const char *cmp, size_t size);
void				get_str_for_search(char *str, t_line *line, int cursor_pos);
void				ft_affiche_brackets(char *content, t_line *line);
void				affiche_files(t_affichfile *afffile, t_affcmpl *head,
	t_line *line);
void				stock_path_file(char *str, t_line *line,
	t_affcmpl **affcmpl);
int					cheker_history_expansion(char *str);
char				*get_node(char *str);
char				*get_all_value(int i);
char				*check_error(char *str);
char				*ft_is_not_pair(int i, char *rest_value);
void				update_cur_mode_r(t_line *line, int prompt_len);
void				ft_disable_mode_r(t_line *line);
int					get_index_mode_r(t_line *line, int *index);
int					check_error_fc(t_opt *opt);
int					check_valide_opt(t_opt *opt, char *hold, int i);
void				free2dm(char ***str);
#endif

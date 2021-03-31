/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <yabakhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 23:01:13 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/30 12:41:36 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# include "error_msg.h"
# include "libft.h"
# include "readline.h"
# include "env.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <dirent.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <time.h>
# include <limits.h>
# include <string.h>
# include <signal.h>
# define METACHARACTER " \n\t;"
# define PIPE "|"
# define AGG_REDI "<>&"
# define DEFAULT_FD_OUT "1"
# define DEFAULT_FD_IN "0"
# define MAX_INDEX 4096
# define EXP	1
# define NOT_EXP 0
# define MIN_INDEX 1024

# define IS_RUNNING 1
# define IS_SUSPENDED 2
# define IS_TERMINATED 4
# define IS_SELECTED 8
# define IS_BACKGROUD 16
# define IS_FOURGROUND 32

# define JOB_PIDS 1
# define JOB_MAIN 2
# define JOB_RUNNING 8
# define JOB_DETAILS 4

# define CURRENT_JOB 1
# define PREV_JOB 2
# define TABLE_SIZE 1000

pid_t					g_pid;
int						g_id;
char					*g_commandline;

enum {
	F_TOKENZ,
	F_TMP,
	F_AST,
	F_STR,
	F_G_HIS,
	F_JOBS
};

typedef enum			e_split{
	Normal,
	Continue,
	Break,
	ReturnNull,
	Returnagg
}						t_split;

typedef struct			s_alias
{
	char				*name;
	char				*value;
	struct s_alias		*next;
}						t_alias;

t_alias					*g_alias;

typedef struct			s_a_v
{
	char				*tmp;
	char				*ptr;
	char				*value;
	char				*startline;
	char				*endline;
	int					start;
	t_alias				*catch;
	t_alias				*head;
}						t_a_v;

typedef struct			s_c_v
{
	int					i;
	char				*ptr;
	int					old_i;
	int					flag;
}						t_c_v;

size_t					g_agg_len;
char					*g_tty_name;
int						g_the_status;

typedef struct			s_mypipe
{
	int					pipe[2];
	pid_t				pid;
	pid_t				g_pid;
	int					temp;
	int					cmd_no;
	int					status;
}						t_mypipe;

typedef	struct			s_ht
{
	char				*value;
	char				*key;
	int					hits;
	struct s_ht			*next;
}						t_ht;

typedef	struct			s_hash
{
	t_ht				**list;
}						t_hash;

t_hash					*g_hashtable;
char					*g_binfile;

typedef struct			s_pointt
{
	int					node_index;
	void				*node_addr;
	int					aggr_index;
	int					pipe_index;
	int					no_space;
}						t_pointt;

typedef struct			s_c_b
{
	int					i;
	int					flag;
	int					j;
}						t_c_b;

typedef struct			s_env
{
	char				*env_var_name;
	char				*env_var_value;
	struct s_env		*next;
}						t_env;

typedef enum			e_type
{
	WORD = 1,
	METACHAR,
	L_REDIR,
	AGGR_SYM,
	R_REDIR,
	PIPE_SYM,
	DQUOT,
	SQUOT,
	EXPANSION,
	SEP,
	AMPER,
	AND,
	OR,
	ENV
}						t_type;

typedef struct			s_quote
{
	char				*string;
	size_t				size;
}						t_quote;

typedef struct			s_lexer
{
	t_pointt			coor;
	char				*data;
	t_type				type;
	struct s_lexer		*next;
}						t_lexer;

typedef struct			s_his
{
	char				*data;
	struct s_his		*next;
}						t_his;

t_his					*g_his;
int						g_alltokenzsize;

typedef struct			s_redir
{
	char				*lfd;
	char				*rfd;
	char				*sym;
	struct s_redir		*next;
}						t_redir;

typedef struct			s_miniast
{
	char				**cmd;
	int					mode;
	int					logic_op;
	int					no_space;
	t_redir				*redirection;
	struct s_miniast	*pipe;
	struct s_miniast	*sep;
}						t_miniast;

t_miniast				*g_tree;

typedef struct			s_mystruct
{
	int					i;
	int					j;
	int					flag;
	int					position;
	size_t				size;
	char				c;
	char				**arr;
	char				*str;
	char				*tmp;
	int					status[2];
	t_miniast			*ast;
	t_lexer				*tokenz;
	t_env				**env_list;
	t_pointt			coord;
}						t_mystruct;

typedef struct			s_split_redir
{
	size_t				i;
	size_t				j;
	char				**agg;
	char				*tmp;
	int					active_word;
	size_t				delim_len;
	size_t				len;
	size_t				agg_len;
	size_t				agg_len_str;
	int					status;
}						t_split_redir;

typedef	struct			s_getfullcmd
{
	char				*cmd;
	char				*tmp;
	char				*to_free;
	int					quote_opened;
	int					i;
	char				c;
	int					flag;
	int					read;
}						t_getfullcmd;

typedef struct			s_here_doc
{
	int					flag;
	char				*text;
	char				*tmp;
	char				*buffer;
}						t_here_doc;

typedef struct			s_expand
{
	char				**arr;
	char				**value;
	char				*string;
	char				*tmp;
	int					i;
	int					j;
	int					val_size;
}						t_expand;

typedef struct			s_expansion
{
	int					i;
	int					j;
	int					data_size;
	char				*data;
	char				*env_value;
	char				*buf;
}						t_expansion;

typedef struct			s_tilde_exp
{
	int					i;
	char				*home_value;
	char				*user;
	char				*user_name;
}						t_tilde_exp;

typedef struct			s_get_bin
{
	int					i;
	char				*bin_file;
	char				*env_path_value;
	char				**dirs;
	char				*tmp;
	char				*tmp2;
}						t_get_bin;

typedef	struct			s_job_ctrl
{
	int					job_id;
	int					c;
	pid_t				grp_pid;
	int					status;
	int					mode;
	char				**cmd;
	struct s_job_ctrl	*next;
}						t_job_ctrl;

typedef struct			s_f_g
{
	int					status;
	int					fd;
	t_job_ctrl			*ptr;
	int					job_id;
}						t_f_g;

typedef struct			s_cd
{
	int					i;
	int					args_no;
	char				*new_path;
	char				*cwd;
	char				buff[MAX_INDEX];
}						t_cd;

typedef struct			s_wlen
{
	int					len;
	int					type;
	int					index;
}						t_wlen;

typedef struct			s_wc
{
	int					i;
	int					flag;
	int					res;
}						t_wc;

typedef struct			s_cd_smpl
{
	struct stat			st;
	char				*tmp;
	char				*tmp2;
}						t_cd_smpl;

t_job_ctrl				*g_jobs_lst;
t_job_ctrl				*g_copy;
t_env					*g_head;

void					source_sh(t_env **head);
char					*here_doc(char *delim);
void					append_list(t_lexer **root, char *data, t_type type,
	t_pointt *cor);
void					init_coord(t_pointt *cor);
void					append_list_redi(t_lexer **root, char *data,
	t_type type, t_pointt *cor);
void					append_list_pipe(t_lexer **root, char *data,
	t_type type, t_pointt *cor);
t_lexer					*lexer(char *buf, t_env **head, t_pointt *coord);
t_quote					*quote_handling(char *s, char quote, int start);
int						parse_pipe(t_lexer **token_node, char *str,
	t_pointt *coor);
int						check_tokenz_grammar(t_lexer *tokenz);
int						expansion_function(char *buf, t_lexer **tokenz,
	t_pointt *coord, t_env **env_list);
int						sep_function(t_lexer **tokenz, t_pointt *cor);
int						aggr_function(char *str, t_pointt *cor,
	t_lexer **lexer);
int						quote_function(char *buf, t_lexer **tokenz,
	t_pointt *cord, char *quote);
int						token_is_sep(int type);
int						quote_handling_function(t_lexer **token_node,
	t_quote *quot, char quote, t_pointt *coord);
int						simple_word_function(char *buf,
	t_lexer **token_node, t_pointt *coord, t_env **head);
int						execute(t_miniast *tree, t_env **env_list);
int						execute_pipes(t_miniast *tree,
	char **tabs, t_env **env_list);
void					execute_direct(char **cmd, char **tabs);
void					execute_undirect(char **cmd, char **tabs, t_env **env);
void					execute_blt_without_fork(t_miniast *tree,
	char **cmd, char **tabs, t_env **env_list);
void					execute_blt_with_fork(t_miniast *tree
, t_env **env_list);
int						execute_redirection(t_redir *redirections,
	char *tty_name);
int						ft_redirect_in_out(t_redir *redirections,
	t_redir *prev, int fd);
char					*ignore_blanks(char *str);
int						back_read(t_getfullcmd *v, int *len, char **ptr);
void					assign_v(t_getfullcmd *v);
int						check_type_(t_type type);
int						setenv_exist(t_lexer *lst);
void					env_update(t_lexer **tokenz, t_env **env_list);
char					**get_setenv_args(t_lexer *lst);
int						append_redir(t_redir *redirection, t_redir *prev);
int						here_document(t_redir *redirection, char *tty_name);
int						agg_redirection(t_redir *redirections,
	t_redir *prev, int fd);
bool					is_quote(int c);
size_t					ft_strlen_char(char *s, char c);
size_t					ft_strlen_char2(char *s, char c, char c2);
size_t					ft_strlen_char_2(char *s, char c, char c2);
char					*ft_strchr_blank(const char *str, int c);
int						check_command_redir(t_lexer **head, char *buf,
	t_pointt *cor);
t_type					last_node_type(t_lexer *tokenz);
char					**strsplit(char const *s);
int						ft_is_aggr(char c);
void					backslash_checker(t_getfullcmd *v, int *len,
	char **tmp);
t_quote					*quote_completion(t_quote **data, char quote);
size_t					get_list_size(t_lexer *tokenz);
char					*get_left_fd_(char *buf);
char					**list_to_tabs(t_env **env_list);
char					*get_bin_file(char **cmd, t_env **env);
int						env_exist(t_env **env_list, char *var_name);
void					modify_env(t_env **env_list, char *var_name,
	char *var_value);
char					*get_cwd(void);
void					gen_oldpwd(char *cwd, t_env **env_list);
void					gen_pwd(char *new_path, t_env **env_list);
int						ft_str_is_digit(char *lfd);
int						check_builtins(char *cmd_name);
int						check_args_no(char **cmd);
void					type_builtin(char **cmd, t_env **env_list);
char					*join_all_bufs(t_his *his);
int						str_is_blank(char *buffer);
char					*get_content_quote(char *buffer,
	char c, t_pointt *coord, int flag_c);
char					*expansion_brackets(char *buf, t_mystruct *v);
int						check_builtins_nfrk(char *cmd_name);
int						get_the_word(char *buf,
	t_lexer **token_node, t_pointt *coord, t_env **head);
size_t					get_arr_size_tokenz(t_lexer *token);
int						is_env(t_lexer **token);
int						ft_agg_digit(t_redir *redirection, int fd, int lfd);
int						ft_agg_close(t_redir *redirection,
	int fd, int lfd);
int						ft_agg_word(t_redir *redirection,
	t_redir *prev, int fd, int lfd);
char					*get_dollars(char *buf);
char					*get_splitter(char *buf, t_mystruct *v);
int						ft_agg_out(t_redir *redir, t_redir *prev, int fd);
int						ft_agg_in(t_redir *redir, t_redir *prev, int fd);
size_t					countall_arr(char **agg, size_t delime_len);
char					*redirection_varname(char ***arr, char *str, size_t *i);
int						split_varname(t_split_redir *v, char *str);
int						split_herdoc(t_split_redir *v, char *str);
void					ft_ctrlc(int sig_no);
char					*handel_signal(t_getfullcmd *v);
void					flag_g(char **av, t_env **env_list, time_t *now);
int						ft_str_is_digit(char *lfd);
void					ft_reset_fd(char *tty_name, int file_d);
int						parse_commands(t_miniast **head,
	t_lexer *tokenz, t_env **env);
char					*ft_strjoin_until_char(char const *s1, char const *s2,
	char c);
void					print_sigpip_int(int status);
char					**fill_node(t_lexer *token,
	t_redir **redirections, t_env **env, int alltoken_size);
int						check_grammar_tokenz(t_lexer *tokenz);
int						fill_cmd_redir(t_lexer *token,
	int *i, t_redir **redirections);
void					fill_cmd(char **ret,
	t_lexer *token, int *i, t_env **env);
void					fill_redirections(t_redir **node, t_lexer *token);
size_t					calc_arr_size(t_lexer *token, int *next_type);
void					stock_env(char **env, t_env **head);
int						addtolist(t_env **head,
	char *var_name, char *var_value);
void					deletenode(t_env **head_ref, char *env_name);
char					**split_redir(char *str);
size_t					redirerction_parse(t_lexer **token_node,
	char **agg, t_pointt *cor);
void					ft_reset_fd(char *tty_name, int file_d);
void					blt_echo(char **cmd, t_redir *redirection);
void					blt_setenv(char **cmd, t_env **env_list);
void					blt_unsetenv(char **cmd, t_env **env_list);
void					blt_cd(char **cmd, t_env **env_list);
char					*get_history(t_lexer *tokenz);
int						expansion_parse(t_lexer **token_node,
	char *buf, t_env **env_list, t_pointt *cor);
char					*get_value_expansion(char *env_name, t_env **head);
int						ft_is_expansion(char *str);
int						ft_is_tilde(char *str);
char					*expanded(t_env **head, char *str);
void					tilde_exp(char *exp, char **data, t_env **env_list);
void					print_env_list(t_env **head);
void					print_arr(char **arr);
void					print_btree(t_miniast *ast);
void					ft_putendl_fd_error(char *s1,
	char *s2, char *s3, char *s4);
void					prompt_completion(char quot);
void					ft_put_multistring2(char **strings);
void					ft_free_arr(char **arr);
void					ft_free_tokenz(t_lexer **head);
void					ft_free_tree(t_miniast **tree);
void					ft_free_his(t_his **g_his);
char					*err_ret(char *s, char *addrr);
void					error_message(char *err_message, int flag);
int						print_error_sym(t_type type);
void					exit_blt(char **cmd);
void					free_env_list(t_env **head);
void					free_vars(t_mystruct *v, int *to_free, int size);
void					execute_pipes2(t_miniast *tree, t_mypipe *pipes);
int						execute_pip_child(t_miniast *tree, t_mypipe *pipes,
char					**tabs, t_env **env_list);
void					sig_groupe(void);
char					**get_pipes_members(t_miniast *lst);
void					append_job(char **arr, t_mypipe pipes, int mode);
char					**get_job_members(t_miniast *tree);
void					expansion_func(t_expand *v, t_env **head);
void					exp_parse_init(t_expansion *v, char **buf);
void					exp_chek(char *buf, t_expansion *v);
int						is_background(t_lexer *tokenz);
int						is_logic_op(t_lexer *tokenz);
int						env_skip(t_lexer **token, int *type);
int						delete_node(t_job_ctrl **head_ref, int g_pid);
void					jobs_blt(char **cmd);
void					main_infos(t_job_ctrl *ptr);
void					checkchild2(int sig);
void					print_job_node(int g_pid);
void					pid_infos(t_job_ctrl *ptr);
void					details_infos(t_job_ctrl *ptr);
int						fg_blt(char **cmd);
int						bg_blt(char **cmd);
int						brackets(char *str);
char					*get_the_line(const char *buf);
void					sub_shell_exec(char *line, t_lexer **tokenz,
	t_env **env_list);
t_hash					*ht_create(void);
char					*ft_hashtable(char **args, char **tabs,
	t_hash **h_table, char **print);
void					ft_hash(char **args, t_hash **h_table);
void					reset_hits(char **args, t_hash **h_table);
void					delete_hashtable(t_hash **h_table, int len);
void					aff_hashtable(t_hash **h_table);
t_ht					*del_list(t_ht **list, int len);
int						hash_function(char *str);
t_ht					*ht_insert(char *str, char **tabs, char **print);
void					l_flag(t_hash **h_table, char **args);
void					del_hash(t_hash **h_table, char **args);
int						delete_list(t_ht *list, t_ht **main_head, char *arg);
void					d_flag(t_hash **h_table, char **args);
void					t_flag(t_hash **h_table, char **args);
void					p_flag(t_hash **h_table, char **args);
void					search_hash(t_hash **h_table, char **args,
	int len);
t_ht					*hash_p_insert(char *arg, char *path);
void					ft_hash_error(char *str);
void					l_flag_error(char *str);
void					l_flag_print(char *value, char *key);
void					l_flag_mini(char *str, t_ht *current);
void					l_flag_valid(t_hash *hashtable, int slot);
void					p_flag_mini(char **args, t_hash **h_table);
void					p_flag_free(t_ht **h_list, char *str, char *path);
int						free_node(t_ht **list);
void					del_list_mini(t_ht **list, int len);
void					search_hash_mini(t_hash **h_table, char **args);
char					*valid_path(char *cmd_name, char **tabs, char **print);
t_ht					*alloc_list(t_ht *list);
t_hash					*alloc_hash(t_hash **h_table);
char					*ft_hash_complete_s(t_hash *hashtable,
	char **args, char **tabs, char **print);
int						ft_hash_complete(char **print, char **args);
char					*absolute_path(char *path, char *command);
int						ft_argslen(char **arr);
int						ft_test(char **args);
int						test_file(char **args);
int						block_special(char *pathname);
int						character_special(char *pathname);
int						is_dir(char *pathname);
int						file_exist(char *pathname);
int						ft_setgid(char *pathname);
int						is_symlink(char *pathname);
int						is_fifo(char *pathname);
int						is_file(char *pathname);
int						readable_by_owner(char *pathname);
int						is_socket(char *pathname);
int						file_not_empty(char *pathname);
int						ft_setuid(char *pathname);
int						writeable_by_owner(char *pathname);
int						executable_by_owner(char *pathname);
int						test_string(char **args);
int						ft_equal(char *str1, char *str2);
int						ft_not_equal(char *str1, char *str2);
int						ft_integer_equal(char *s1, char *s2);
int						ft_integer_not_equal(char *s1, char *s2);
int						ft_integer_ge(char *s1, char *s2);
int						ft_integer_lt(char *s1, char *s2);
int						ft_integer_le(char *s1, char *s2);
int						ft_argslen(char **args);
int						ft_is_numeric(char *str);
void					error_test(char *str);
int						test_file_complete(char **args);
char					*get_value_expansion_path(char *env_name);
char					*get_value_expansion_cd(char *env_name, t_env **head);
void					ft_fixenv(t_lexer **token);
void					ft_envcpy(t_env **head);
void					ft_execenv(t_env **head, t_lexer *tokenz, int flag);
int						ft_tmpvarcheck(t_lexer *tokenz);
void					ft_addtmpvar(t_env **head, char *data);
void					free2dm(char ***str);
void					clean_vars(t_a_v *vars, int flag);
char					*return_value(char *name, t_alias *alias);
int						is_indice(int c);
int						counter(char **str);
t_alias					*copy_list(t_alias *alias);
void					init_alias(t_a_v *vars, int s, int e, char **line);
int						if_del_found(t_c_v *var, char **line);
int						check_line_var(t_c_v *var, t_alias **alias,
	char **line);
void					alias_check(char **line, t_alias **alias);
void					alias_bultin(char **line, t_alias **alias);
void					get_start_end_line(t_a_v *vars, char **line, int e,
	t_alias **alias);
int						if_no_start_line(t_a_v *vars, char **line, int *s,
	int *e);
int						if_there_start_line(t_a_v *vars, char **line, int *s,
	int *e);
void					printfx(char **line, int s, int e, t_alias **alias);
void					replace_line(int *s, int e, char **line);
char					*ft_strdup_from_to(const char *s, int start, int end);
t_alias					*check_alias_repeate(char *name, t_alias *alias);
void					del(void *s, void *str);
void					ft_one_alias_del(t_alias **alst,
	void (*del)(void *, void *));
void					free_alias_list(t_alias **alst,
	void (*del)(void *, void *));
void					add_to_alias_file(char *line, t_alias **alias);
void					add_alias_list_to_file(t_alias *alias);
int						isthere_alnum(char *str);
int						checker_alias(char **str);
int						if_i_found_it(t_alias *pr, t_alias *ptr, t_alias **al,
	char *str);
void					get_value_from_list(char *line, t_alias *alias,
	int flag);
void					create_alias_list(void);
t_alias					*alias_create(char *name, char *value);
t_alias					*alias_lst_adder(t_alias **old, t_alias *new);
void					delete_alias_var(t_alias **alias, char **str);
void					ft_move_replace(char *str);
void					execute_fc(char *line);
void					print_tokenz(t_lexer *tokenz);
t_lexer					*move_list(t_lexer *tokenz, int alltokenzsize);
#endif

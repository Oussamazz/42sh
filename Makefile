NAME= 42sh
LIBFT_PATH= ./libft/
INCLUDE= -I ./includes/  -I $(LIBFT_PATH)
INC = ./includes/sh.h ./includes/readline.h ./includes/error_msg.h

SRC_DIR_PARSE:= ./SRC_HEAD/
OBJ_DIR_HEAD:= ./objs/

FLAGS = -Wall -Wextra -Werror

SRC_ENV= dbl_func.o list_func.o  set.o       tools1.o     vartools.o tools2.o

SRC_TOOLS = get_pipes_members.o argslen.o brackets.o alias.o alias_bultin.o counter.o free_alias_list.o manage_alias_file.o manage_alias_line.o manage_alias_list.o

SRC_EXECUTION = execute.o execute_cmd.o execute_builtins.o execute_pipes.o execute_fc.o  tools1.o  tools2.o 

SRC_BUILTINS = blt_echo.o  exit_blt.o type_blt.o cd_blt.o fg_blt.o bg_blt.o

SRC_EXPANSION = expand.o expansion.o tild_expansion.o get_value_exp.o tools1.o

SRC_PARSING = ast.o check_grammar.o lexer.o lexercore.o split.o fill.o tools.o get_the_line.o tools1.o tools2.o

SRC_PIPE_REDIRECTION =	agg_redir.o here_doc.o redirections.o \
						split_redir.o agg_in_out.o split_tools.o

SRC_MAIN =	envirement.o error_handler.o free1.o\
			ft_free.o his.o main.o node.o printing.o utils.o utils2.o quote_handling.o signals.o here_doc_fd.o \
			utils3.o utils4.o utils5.o utils6.o printing_jobs.o tools1.o

SRC_HASH = alloc_hash.o errors_print.o flags.o h_tools.o hash_tools.o hash_tools2.o hashtable.o

SRC_TEST = ft_test.o test_file.o test_file_tools1.o test_file_tools2.o test_s_and_n_tools.o test_string_and_numeric.o

SRC_READLINE = ft_readline.o history.o keys_alt.o move_cursor.o selection.o tools_readline.o builtins_readline.o prepare_readline.o \
				signal_readline.o helper_readline.o mode_r.o auto_completion.o read_fc.o fc_l.o fc_e.o history_expansion.o \
				tools_auto_completion.o builtine_auto_completion.o fc_s.o tools_comletion.o tools_comlition_file.o tools_fc_l.o history_expansion_tool.o tools_fc.o mode_r_builtins.o tools_history.o checker_fc.o prepare_read_fc.o
SRC_JOB_CTRL = nodes_jobs.o get_job_members.o jobs_blt.o show_info.o


OBJ_MAIN = $(addprefix objs/src/, $(SRC_MAIN))
OBJ_ENV = $(addprefix objs/envv/, $(SRC_ENV))
OBJ_TEST = $(addprefix objs/builtin_test/, $(SRC_TEST))
OBJ_HASH = $(addprefix objs/hashtable/, $(SRC_HASH))
OBJ_READLINE = $(addprefix objs/readline/, $(SRC_READLINE))
OBJ_EXPANSION = $(addprefix objs/expansion/, $(SRC_EXPANSION))
OBJ_PARSING = $(addprefix objs/parsing/, $(SRC_PARSING))
OBJ_BUILTINS = $(addprefix objs/builtins/, $(SRC_BUILTINS))
OBJ_EXECUTION = $(addprefix objs/execution/, $(SRC_EXECUTION))
OBJ_PIPE_REDIRECTION = $(addprefix objs/pipe_redirection/, $(SRC_PIPE_REDIRECTION))
OBJ_JOB_CTRL = $(addprefix objs/control_jobs/, $(SRC_JOB_CTRL))
OBJ_TOOLS = $(addprefix objs/tools/, $(SRC_TOOLS))

OBJECT = $(OBJ_EXPANSION) $(OBJ_BUILTINS) $(OBJ_PARSING) $(OBJ_PIPE_REDIRECTION)  $(OBJ_MAIN) $(OBJ_READLINE) $(OBJ_EXECUTION) $(OBJ_TOOLS) $(OBJ_JOB_CTRL) $(OBJ_HASH) $(OBJ_TEST) $(OBJ_ENV)
CURRENT_OBJ_DIR = objs

all: $(NAME)

$(NAME): $(OBJECT) $(INC)
	@make -sC $(LIBFT_PATH)
	@gcc $(FLAGS) $(OBJECT) $(INCLUDE) -L $(LIBFT_PATH) -lft -ltermcap -o $(NAME)
	@echo "\033[1m\033[35m|⩺▾ 42sh Successfully Created ☯ ⩹|\033[0m"

$(OBJ_DIR_HEAD)%.o : $(SRC_DIR_PARSE)%.c
	$(eval CURRENT_OBJ_DIR=$(shell sh -c "echo $^ |  cut -d / -f 2"))
	@mkdir -p $(OBJ_DIR_HEAD)/$(CURRENT_OBJ_DIR)
	@gcc $(FLAGS) -c $^ $(INCLUDE) -o $@
	@echo "\033[92m|⩺  Object file Created ⩹|"

clean:
	@echo "\033[1m\033[93m|⩺  cleaning...\033[0m"
	@make clean -sC  $(LIBFT_PATH)
	@rm -rf $(OBJ_DIR_HEAD)

fclean: clean
	@make fclean -sC $(LIBFT_PATH)
	@rm -f $(NAME)
	@echo "\033[92m|⩺  42sh executable & object files REMOVED!\033[0m"

re: fclean all

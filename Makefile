NAME= minishell
READLINE_PATH= $(shell brew --prefix readline)
CC= cc
CFLAGS= -Wall -Wextra -Werror -I $(READLINE_PATH)/include
COMPILE= $(CC) $(CFLAGS)
PARCUNG_HEADER= srcs/parcing/minishell.h
EXECUTION_HEADER= srcs/execution/execution.h
ERRORS= srcs/execution/errors
BUILTINS_COMMANDES= srcs/execution/builtins_commandes
ENVIREMENT= srcs/execution/envirement
FILSES_AND_REDIRECTIONS= srcs/execution/files_and_redirections
GENERAL_UTILS= srcs/execution/general_utils
MULTIPLE_COMMANDES= srcs/execution/multiple_commandes
STATUS= srcs/execution/status
ONLY_TWO_COMMANDES= srcs/execution/only_two_commandes
ONLY_ONE_COMMANDE= srcs/execution/only_one_commande

SRC_ILES_PARCING= srcs/parcing/main.c srcs/parcing/utils1.c srcs/parcing/new_split.c \
		srcs/parcing/tokenizing.c srcs/parcing/utils2.c  srcs/parcing/expanding.c \
 		srcs/parcing/ft_env.c srcs/parcing/list_utils.c srcs/parcing/cmds_list_func.c \
 		srcs/parcing/heredoc.c srcs/parcing/cmds_list_utils.c\
		srcs/parcing/expanding_utils2.c srcs/parcing/parse_utils.c\
		srcs/parcing/expanding_utils1.c srcs/parcing/heredoc_utils.c\
		srcs/parcing/signals_utils.c srcs/parcing/cmds_list_utils2.c\
		srcs/parcing/cmds_list_utils3.c srcs/parcing/parse_utils2.c\
		srcs/parcing/ft_env_utils.c srcs/parcing/tools.c

SRC_FILES_EXECUTION= $(BUILTINS_COMMANDES)/builtins_1.c \
					$(BUILTINS_COMMANDES)/builtins_2.c \
					$(BUILTINS_COMMANDES)/unset.c \
					$(BUILTINS_COMMANDES)/export.c \
					$(BUILTINS_COMMANDES)/export_utils.c \
					$(BUILTINS_COMMANDES)/export_utils_2.c \
					$(BUILTINS_COMMANDES)/execute_echo.c \
					$(BUILTINS_COMMANDES)/builtins_check.c \
					$(BUILTINS_COMMANDES)/builtins_errors_utils.c \
					$(ENVIREMENT)/commande_utils.c \
					$(ENVIREMENT)/store_envirement.c \
					$(ERRORS)/minishell_errors_1.c \
					$(ERRORS)/minishell_errors_2.c \
					$(ERRORS)/minishell_errors_3.c \
					$(FILSES_AND_REDIRECTIONS)/files_handlling.c \
					$(FILSES_AND_REDIRECTIONS)/files_redirection.c \
					$(FILSES_AND_REDIRECTIONS)/files_utils_1.c \
					$(FILSES_AND_REDIRECTIONS)/files_utils_2.c \
					$(GENERAL_UTILS)/my_utils_1.c \
					$(GENERAL_UTILS)/my_utils_2.c \
					$(GENERAL_UTILS)/my_utils_3.c \
					$(GENERAL_UTILS)/split.c \
					$(MULTIPLE_COMMANDES)/mlp_cmd_alloc.c \
					$(MULTIPLE_COMMANDES)/mlp_cmd_clean.c \
					$(MULTIPLE_COMMANDES)/mlp_cmd_dup.c \
					$(MULTIPLE_COMMANDES)/mlp_cmd_err.c \
					$(MULTIPLE_COMMANDES)/mlp_cmd_utils_2.c \
					$(ONLY_ONE_COMMANDE)/execute_one_cmd.c \
					$(MULTIPLE_COMMANDES)/mlp_cmd_utils.c \
					$(ONLY_TWO_COMMANDES)/execute_two_cmd.c \
					$(STATUS)/status_utils.c \
					srcs/execution/start_execution.c
OBJ_FILES_PARC = $(SRC_ILES_PARCING:.c=.o) 
OBJ_FILES_EXEC =  $(SRC_FILES_EXECUTION:.c=.o)

LDFLAGS = -lreadline -L $(READLINE_PATH)/lib

all: $(NAME)

srcs/parcing/%.o: srcs/parcing/%.c  $(PARCUNG_HEADER) $(EXECUTION_HEADER) libft/libft.h
	$(COMPILE) -c $< -o $@

srcs/execution/%.o: srcs/execution/%.c $(EXECUTION_HEADER) $(PARCUNG_HEADER) libft/libft.h
	$(COMPILE) -c $< -o $@

$(NAME): $(OBJ_FILES_PARC) $(OBJ_FILES_EXEC)
	$(COMPILE) $(OBJ_FILES_PARC) $(OBJ_FILES_EXEC) $(LDFLAGS) -o $(NAME) libft/libft.a

clean:
	rm -f $(OBJ_FILES_PARC) $(OBJ_FILES_EXEC)

fclean: clean
	rm -f $(NAME)   

re: fclean all
  
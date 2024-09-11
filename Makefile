NAME = minishell
CFILES = srcs/main.c srcs/utils1.c  \
 srcs/new_split.c srcs/tokenizing.c srcs/utils2.c  srcs/expanding.c \
 srcs/ft_env.c srcs/list_utils.c srcs/cmds_list_func.c srcs/heredoc.c
OFILES = $(CFILES:.c=.o)
CFLAGS = -Wall -Wextra  -Werror #-fsanitize=address -g
LDFLAGS = -lreadline
CC = cc

all: $(NAME)

%.o: srcs/%.c includes/minishell.h
	$(CC) $(CFLAGS) -c $< 

$(NAME): $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) $(LDFLAGS)  -o $(NAME) libft/libft.a

clean:
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

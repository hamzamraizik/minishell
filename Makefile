NAME = minishell
CFILES = main.c utils1.c  \
 new_split.c tokenizing.c utils2.c  expanding.c \
 ft_env.c list_utils.c cmds_list_func.c
OFILES = $(CFILES:.c=.o)
CFLAGS = -Wall -Wextra  -Werror #-fsanitize=address -g
LDFLAGS = -lreadline
CC = cc

all: $(NAME)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< 

$(NAME): $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) $(LDFLAGS)  -o $(NAME) libft.a

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

NAME = minishell
CFILES = main.c utils1.c  \
 new_split.c tokenizing.c utils2.c tkherbi9.c expanding.c \
 ft_env.c list_utils.c cmds_list_func.c
OFILES = $(CFILES:.c=.o)
CFLAGS = -Wall -Wextra  -Werror #-fsanitize=address -g
LDFLAGS = -L/usr/lib/x86_64-linux-gnu -lreadline
CC = gcc

all: $(NAME)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< 

$(NAME): $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) $(LDFLAGS)  -o $(NAME) libft.a

clean:
	rm *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

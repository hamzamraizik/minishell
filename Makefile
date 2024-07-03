NAME = minishell
CFILES = main.c
OFILES = $(CFILES:.c=.o)
CFLAGS = -Wall -Wextra -Werror
CC = gcc

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@
all: $(NAME)
$(NAME): $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -o $(NAME)
clean:
	rm *.o
fclean: clean
	rm -f $(NAME)
re: fclean all
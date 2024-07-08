NAME = minishell
CFILES = main.c utils1.c
OFILES = $(CFILES:.c=.o)
CFLAGS = -Wall -Wextra -Werror
CC = gcc

all: $(NAME)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $<

$(NAME): $(OFILES)
	$(CC) $(CFLAGS)  -lreadline $(OFILES) -o $(NAME)

clean:
	rm *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

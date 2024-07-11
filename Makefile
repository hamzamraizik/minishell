NAME = minishell
CFILES = main.c utils1.c  ft_strlen.c  ft_strchr.c  ft_strjoin.c  ft_strdup.c \
 ft_memcpy.c ft_split.c ft_substr.c new_split.c tokenizing.c
OFILES = $(CFILES:.c=.o)
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L/usr/lib/x86_64-linux-gnu -lreadline
CC = gcc

all: $(NAME)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $<

$(NAME): $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) $(LDFLAGS)  -o $(NAME)

clean:
	rm *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

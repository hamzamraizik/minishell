NAME = minishell
CFILES = main.c utils1.c  ft_strlen.c  ft_strchr.c  ft_strjoin.c  ft_strdup.c \
 ft_memcpy.c  ft_substr.c ft_split.c new_split.c tokenizing.c utils2.c tkherbi9.c expanding.c \
 ft_env.c
OFILES = $(CFILES:.c=.o)
CFLAGS = -Wall -Wextra -Werror -g
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

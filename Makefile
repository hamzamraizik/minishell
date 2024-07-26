NAME = minishell
CFILES = main.c utils1.c new_split.c tokenizing.c utils2.c tkherbi9.c expanding.c ft_env.c
LIBFTCFILES = libft/ft_strlen.c libft/ft_strchr.c libft/ft_strjoin.c libft/ft_strdup.c \
 libft/ft_memcpy.c libft/ft_substr.c libft/ft_split.c
LIBFTOFILES = $(LIBFTCFILES:.c=.o)
OFILES = $(CFILES:.c=.o)
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -L/usr/lib/x86_64-linux-gnu -lreadline
CC = gcc

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

libft/%.o: libft/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OFILES) $(LIBFTOFILES)
	$(CC) $(CFLAGS) $(OFILES) $(LIBFTOFILES) $(LDFLAGS) -o $(NAME)

clean:
	rm -f $(OFILES) $(LIBFTOFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

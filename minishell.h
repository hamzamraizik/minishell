#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

# define RED  "\x1B[31m"
# define GRN  "\x1B[32m"

typedef enum e_tokens
{
	PIPE	= 1,
    HEREDOC	= 2,
    APPEND	= 3,
    TRUNC	= 4,
    IN		= 5,
    OUT		= 6,
    VAR     = 7,
    SEMI   = 8,
    // ERR     = 7,
    T_SPACE   = 9,
    WORD    = 10,
    // T_NEWLINE = 11,
}       t_tokenz;

typedef struct s_list
{
	char			*content;
	int				type;
	struct	s_list	*next;
	struct	s_list	*prev;
}   t_list;

int		check_if_empty(char *line);
void	*creat_node(char *content, int type);
void	list_add_back(t_list **head, t_list *new);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1, int n);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_new_split(const char *s, char c, size_t len);
void	tokenizing(t_list **head, char **line);
char    *add_delimetre(char *line);

#endif // MINISHELL_H
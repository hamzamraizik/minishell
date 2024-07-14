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
#include <stdbool.h>
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

//__________________________Libft functions
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1, int n);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
//___________________________parsing functions
char	**ft_new_split(const char *s, char c, size_t len);
void	tokenizing(t_list **head, char **line);
char    *add_delimetre(char *line);
char    *add_spaces(char *line);
int     count_char(char *line, char c);
int     count_new_len(char *line, int old_len);
char	*remove_char(char *line, char c);
//_________________________linked list functions
void	*creat_node(char *content, int type);
void	list_add_back(t_list **head, t_list *new);
//___________________________check functions
int		check_if_empty(char *line);
int     check_special(char c);
int     check_quotes(int is_quotes, char c);

#endif // MINISHELL_H
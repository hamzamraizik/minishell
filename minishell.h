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
#include <ctype.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define RESET   "\033[0m"
#define BOLD    "\033[1m"

extern char **ft_envp;

typedef enum e_tokens
{
	PIPE	= 1,
	HEREDOC	= 2,
	APPEND	= 3,
	TRUNC	= 4,
	IN		= 5,
	OUT		= 6,
	VAR     = 7,
	D_QUOTES = 8,
	T_SPACE   = 9,
	WORD    = 10,
	S_QUOTES = 11,
}       t_tokenz;

typedef struct s_list
{
	char			*content;
	int				type;
	struct	s_list	*next;
	struct	s_list	*prev;
}   t_list;

typedef struct s_env
{
	char    *line;
	char    *tab;
	char    *key;
	char    *value;
}           t_env;
//__________________________Libft functions
char	*ft_strchr(const char *s, int c);
char	**ft_split(char const *s, char c);
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
int     syntax_error(t_list *head);
//_________________________linked list functions
void	*creat_node(char *content, int type);
void	list_add_back(t_list **head, t_list *new);
void    *lstclear(t_list *tmp);
//___________________________check functions
int		check_if_empty(char *line);
int     check_special(char c);
int     check_quotes(int is_quotes, char c);
void    s_with_d_Q(char *s);
// expanding functions
void    expanding(t_list **head);
char    *is_var(char **env, char *var);

#endif // MINISHELL_H
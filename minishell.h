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

typedef struct s_args
{
	int				i;
	int				j;
	int				is_quots;
}		t_args;

typedef enum e_tokens
{
	PIPE	= 1,
	HEREDOC	= 2,
	APPEND	= 3,
	IN		= 5,
	OUT		= 6,
	VAR     = 7,
	WORD    = 10,
	DELEMETRE = 12,
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
int		isnum(char c);
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
char	*add_spaces(char *line, int new_len);
int     count_char(char *line, char c);
int     count_new_len(char *line, int old_len);
void	initial_ints(int *i, int *j, int *k);
char	*remove_char(char *line, char c);
int     syntax_error(t_list *head);
//_________________________linked list functions
void	*creat_node(char *content, int type);
void	list_add_back(t_list **head, t_list *new);
void    *lstclear(t_list *tmp);
t_list  *get_last_node(t_list *head);
//___________________________check functions
int		check_if_empty(char *line);
int     check_special(char c);
int     check_quotes(int is_quotes, char c);
void    s_with_d_Q(char *s);
// expanding functions
void    expanding(t_list **head);
char    *is_var(char **env, char *var);
void	take_previous(char **result, const char *word, int start, int i);

#endif // MINISHELL_H
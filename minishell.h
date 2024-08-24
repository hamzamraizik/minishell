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

// typedef struct s_env
// {
// 	char    *line;
// 	char    *tab;
// 	char    *key;
// 	char    *value;
// }           t_env;
typedef struct s_files
{
	char	**infiles;
	char	**outfiles;
	char	**appendfiles;
	char	**delemetre;
}		t_files;

typedef struct s_cmd
{
	char			**cmd;
	struct s_cmd	*next;
	t_files			files;
}		t_cmd;

//__________________________Libft functions
char	*ft_strchr(  char *s, int c);
int		isnum(char c);
char	**ft_split(char   *s, char c);
char	*ft_strdup(  char *s1, int n);
char	*ft_strjoin(char   *s1, char   *s2);
size_t	ft_strlen(  char *str);
void	*ft_memcpy(void *dest,   void *src, size_t n);
char	*ft_substr(char   *s, unsigned int start, size_t len);
//___________________________parsing functions
char	**ft_new_split(  char *s, char c, size_t len);
void	tokenizing(t_list **head, char **line);
char    *add_delimetre(char *line);
char	*add_spaces(char *line, int new_len);
int     count_char(char *line, char c);
int     count_new_len(char *line, int old_len);
void	initial_ints(int *i, int *j, int *k);
int     syntax_error(t_list *head);
//_________________________linked list functions
void	*creat_node(char *content, int type);
void	list_add_back(t_list **head, t_list *new);
void    lstclear(t_list **tmp);
t_list  *get_last_node(t_list *head);
void	cmd_add_back(t_cmd **head, t_cmd *new);
t_cmd	*new_cmd_node(void);
//___________________________check functions
int		check_if_empty(char *line);
int     check_special(char c);
int     check_quotes(int is_quotes, char c);
void    s_with_d_Q(char *s);
//_________________________expanding functions
void    expanding(t_list **head);
char    *is_var(char **env, char *var);
void	take_previous(char **result,   char *word, int start, int i);
//____________________cmds's list functions
int		count_cmds(t_list *head);
int		count_type(t_list *head, int type);
void	allocate_args(t_list *head, t_files *files);
t_files	fill_files(t_list *head);
t_cmd	*fill_cmds_list(t_list **head);
char	**fill_cmds_array(t_list *head);

#endif // MINISHELL_H
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochangli <ochangli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:47:37 by hmraizik          #+#    #+#             */
/*   Updated: 2024/10/18 03:54:23 by ochangli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <errno.h>
# include <signal.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>
# include "../../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>

/*************************************************/
typedef struct termios	t_termios;
int						g_signal;

//******************* simple struct to fix norm

typedef struct s_args
{
	int				i;
	int				j;
	int				is_quots;
}		t_args;

//******************* Tokenization types

typedef enum e_tokens
{
	PIPE		= 1,
	HEREDOC		= 2,
	APPEND		= 3,
	IN			= 5,
	OUT			= 6,
	VAR			= 7,
	NORMAL_VAR	= 8,
	WORD		= 10,
	DELEMETRE	= 12,
}		t_tokenz;

//******************** first list structure

typedef struct s_list
{
	char			*content;
	int				type;
	struct s_list	*next;
	struct s_list	*prev;
}		t_list;

typedef struct s_my_env
{
	char			*variable;										
	char			*data;
	struct s_my_env	*next;
}				t_my_env;

typedef struct s_infos
{
	char		**envp;
	int			expand_flag;
	int			exit_status;
	t_my_env	*bash_env;
}			t_infos;

typedef struct s_files
{
	char	**infiles;
	char	**outfiles;
	char	**appendfiles;
	char	**delemetre;
	char	**allfiles;
	int		*ambiguous_indexes;
}		t_files;

typedef struct s_cmd
{
	t_list			*head;
	char			**cmd;
	struct s_cmd	*next;
	t_files			files;
}		t_cmd;

void	sig_handler(int signo);

/******************* Parsing functions ***************/

//_________________________parse functions
char	**free_substrs(char **substrs);
int		free_things(void *ptr, void *ptr1, t_list *ptr2);
void	refresh_stat(char *new_line, char *line, t_list *head, t_termios *term);
int		first_syntax_check(char *line);
int		check_multi_pipes(char *line);
int		in_out_check(char *line);
char	**ft_new_split(char *s, char c, int len);
char	*add_delimetre(char *line, int length);
char	*add_spaces(char *line, int new_len);
int		tokenizing(t_list **head, char **line);
int		count_new_len(char *line, int old_len);
void	initial_ints(int *i, int *j, int *k);
int		syntax_error(t_list *head);
int		in_out_check2(char *line, int *i, int *j);
void	put_err(void);
void	sig_int_status(t_infos *infos);
int		add_line_to_history(char *line, t_infos *infos);
//_________________________linked list functions
void	*creat_node(char *content, int type);
int		list_add_back(t_list **head, t_list *new);
void	lstclear(t_list **tmp);
t_list	*get_last_node(t_list *head);
void	cmd_add_back(t_cmd **head, t_cmd *new);
t_cmd	*new_cmd_node(void);
//___________________________check functions
int		check_if_empty(char *line);
int		is_contain_spaces(char *line);
int		check_special(char c);
int		check_quotes(int is_quotes, char c);
int		pipe_before(t_list *tmp);
int		is_empty(char *s);
//_________________________expanding functions
void	expanding(t_list **head, t_infos *infos);
void	update_content(t_list *tmp, t_infos *infos);
int		write_in_file(int ifd[], char *dilimetre, char **buffer, char *line);
int		count_var_words( char *s, char c);
char	*my_getenv_var(char *name, t_infos *infos);
char	*handle_var(t_list *tmp, int heredoc_flag,
			t_infos *infos, char *buffer);
char	*handle_d_q_var(char *str, int *index, t_infos *infos);
void	d_q_var_part2(char **result, char *str, int *start, int *index);
int		normal_var(char **result, char *word, int tab[], t_infos *infos);
char	*handle_s_q_var(char *str, int *index);
char	*remove_var_spaces(char *tmp);
char	*handle_home_symbol(char *str, t_infos *infos);
int		double_dollar_cases(char **result, char *word, int tab[]);
int		special_vars(char **result, char **str, int *start, int *index);
char	*expand_variable(char *str, int *index, t_infos *infos);
int		accepted_chars(t_list *tmp);
void	take_previous(char **result, char *word, int start, int i);
//____________________cmds's list functions
int		count_cmds(t_list *head);
int		allfiles_counter(t_list *head);
int		count_type(t_list *head, int type);
int		allocate_args(t_list *head, t_files *files);
t_files	fill_files(t_list *head);
t_cmd	*fill_cmds_list(t_list **head);
char	**fill_cmds_array(t_list *head);
void	clear_cmds_list(t_cmd **cmd_list);
char	*trim_quotes(char *s);
char	*trim_name_quotes(char *s, int type);
int		fill_cmd(t_list *tmp, char **cmd);
void	terminate_files(t_files *files, int *index);
void	free_files(t_files *files);
int		ft_heredoc(t_cmd *cmd, t_infos *infos);
char	*trim_quotes(char *s);
void	signals(void);
void	fill_filles_prt2(t_list *head, t_files *files, int *index);
//_______________________heredoc functions
void	dil_var_check(char **buffer, int cond, t_infos *infos);
void	sig_hedroc(int signo);
int		update_heredoc_files(t_files *files);
char	*parse_dilimetre(char *s);
//********************************************
char	**env_list_to_array(t_my_env *env, char **envp_tab);
void	update_in_env(char *variable, char *data, t_infos *infos);
char	*get_from_myenv(char *variable, t_infos *infos);
void	quit_handler(int sig_num);
void	update_exit_status(t_infos *infos, int exit_num);
//_______________________env functions
char	**env_list_to_array(t_my_env *env, char **envp_tab);
t_infos	*inistialize_cmd_infos(char **envp);
void	free_lists(t_infos *infos);

#endif // MINISHELL_H

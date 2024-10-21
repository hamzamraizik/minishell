/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochangli <ochangli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 09:44:01 by ochangli          #+#    #+#             */
/*   Updated: 2024/10/18 03:32:35 by ochangli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include "../parcing/minishell.h"
# include <sys/stat.h>

# define MAX_NAME_SIZE 256
# define NO_SUCH_FILE_OR_DIR 127 

typedef struct stat	t_file_type;
/*********************Builtin functions*********************/
/*builtin commandes*/
int			pwd_builtin_exec(t_cmd *data, t_infos *infos);
int			export_builtin_exec(t_cmd *data, t_infos *infos, int i);
int			unset_builtin_exec(t_cmd *data, t_infos *infos);
int			exit_builtin_exec(t_cmd *data, t_infos *infos, int is_onecmd);
int			cd_builtin_exec(t_cmd *data, t_infos *infos);
int			env_builtin_exec(t_cmd *data, t_infos *infos);
/*unset*/
int			not_valid_variable(char *str);
void		free_unsettled_node(t_my_env *node);
int			unset_it(char *variable, t_infos *infos);
/*Export */
void		just_print_export(t_cmd *data, t_infos *infos);
void		export_process(char *var_str, char *data_str,
				char *cmd, t_infos *infos);
int			valid_to_add_it(char *str);
char		*get_variable(char *string);
char		*get_from_myenv(char *variable, t_infos *infos);
char		*get_data(char *string, t_infos *infos);
void		just_print_export(t_cmd *data, t_infos *infos);
int			not_valid_identifier(char *str, t_infos *infos);
void		sort_infos_env(t_my_env *infos);
t_my_env	*copy_env(t_my_env *env);
int			is_alredy_exist(char *variable, t_infos *infos);
//echo
void		ft_putstr_fd_exec(char *str, int fd);
void		exex_echo_no_flag_exec(char **echo_cmd);
void		exex_echo_with_flag_exec(char **echo_cmd);
int			exex_echo_exec(t_cmd *data, t_infos *infos);
void		unset_fails(char *str, t_infos *infos);
void		export_fails(char *str, t_infos *infos);
/*************************libft_functions************************/

int			ft_strlen_exec(const char *str);
int			ft_strcmp_exec(const char *s1, const char *s2, int type);
void		ft_strcpy_exec(char *s1, char *s2);
int			ft_strcmp_2(const char *s1, const char *s2);
t_my_env	*ft_lstnew_exec(char *variable, char *data);
char		*to_lower_exec(char *cmd);
int			ft_lstsize(void *lst);
/**********************envirement_functions********************/

void		ft_lstadd_back_exec(t_my_env **lst, t_my_env *new);
size_t		data_len_exec(char *s);
size_t		var_len_exec(char *s);
char		*get_variable_exec(char *string);
char		*get_data_exec(char *string);
void		get_bash_env_exec(t_my_env **head, char **env);

/***********************************pipex.c************************************/

char		*get_cmd_exec(char *cmd, char **env);
char		*get_path_exec(const char *s, char **envp);
char		*get_full_path_exec(char *cmd, char *path_env);
char		*get_final_path_exec(char *cmd, char **envp);
char		*ft_concatinate_exec(const char *s1, const char *s2, int len);

/*********************** errors functions	********************/

void		free_exit_exec(char **array);
void		cmd_not_found_exec(const char *s);
void		exit_error_exec(char **cmd);
void		commande_not_found_exec(const char *s);
char		**ft_split_exec(const char *s, char c);
void		freing_exec(char **p);
int			ft_strchr_exec(const char *s, int c);
int			ft_space_exec(const char *str);
void		ambiguous_redirect(t_infos *infos);
void		malloc_fails(void);
void		no_file_or_dir(char *s);

/***********************main.c*********************************/

void		initial_execution(t_cmd *data, t_infos *infos);
int			is_builtin_cmd_exec(char *cmd);
int			builtin_cmds_exec(t_cmd *data, t_infos *infos, int is_onecmd);

/*******************executable_cmnds*****************************/

int			files_and_redirections(t_cmd *data, t_infos *infos);

/***************************  one commande *********************/
// files:
int			ft_strmycmp(char *s1, char *s2);
int			get_file_index(char *file_name, char **array);
int			check_can_creat(char **files, int index);
int			creat_files(char **files, t_files allfiles, t_infos *infos);
void		no_file_or_dir_exec(char *cmd);
void		update_exit_status(t_infos *infos, int exit_num);
void		file_does_not_exist(char *file_name);
int			is_ambiguous(char *s, t_files allfiles, int index);
char		*no_path(char	*commande);
char		*with_path(char	*cmd, char	*path_line);

/*************************** two commandes **********************/

void		execute_two_cmd(t_cmd *data, t_infos *infos);
void		execve_commande(t_cmd *data, t_infos *infos);
void		two_commandes(t_cmd *data, t_infos *infos);
int			fork_first_child(t_cmd *data, t_infos *infos, int pp[]);
int			fork_second_child(t_cmd *data, t_infos *infos, int pp[]);
void		execute_two_cmd(t_cmd *data, t_infos *infos);
void		one_single_commande(t_cmd *data, t_infos *infos);
/************************** multiple commandes **********************/
int			initila_and_alloc(int *cmd_infos, int cmd_number,
				int **childs, int ***pipes);
int			*allocate_for_childs(int cmd_number);
void		wait_all(int *childs, t_infos *infos, int cmd_number);
void		execute_multiple_cmds(t_cmd *data, t_infos *infos, int pipes);
int			**allocate_memory_for_pipes(int pipes);
int			close_child_pipes(int **pp, int index);
void		cmd_infos_init(int	*cmd_inf, int num);
void		wait_multiple(int *childs, t_infos *infos,
				int cmd_number, int **pp);
void		pipe_fails(void);
void		free_int_array(void	**array, int size);
void		child_fails(pid_t *childs, int **pp, int pipe_num);
void		dup_fails(int status);
void		execve_fails(void);
void		allocation_pipes_fails(void);
pid_t		creat_first_child(t_cmd	*data, t_infos *infos,
				int	**pp, int *inf);
pid_t		creat_midlle_childs(t_cmd	*data, t_infos *infos,
				int	**pp, int *inf);
pid_t		creat_last_child(t_cmd *data, t_infos *infos, int **pp, int *inf);
int			dup_first_child(int **pp, int *inf);
int			dup_midlle_child(int **pp, int *inf);
int			dup_last_child(int **pp, int *inf);
void		close_all_pipes(int **pp, int *inf);
void		close_pipes(int	**pp, int nbr);
void		free_allocated_pipes(int **pp, int size);
int			**allocate_memory_for_pipes(int pipes);
int			returned_infile_index(t_files files);
int			returned_outfile_index(t_files files);
void		init_fds_index(int *fds);
int			array_lenght(char **array);
void		permission_denied(char *file_name);
int			is_exist_in_array(char **files, char *file_name);
int			redirect_commnde(int infile_fd, int outfile_fd);
void		init_files_index(t_files files, int *indexes);
int			file_opening(t_cmd *data, int *in_out_fd, int *files_index);
int			file_opening(t_cmd *data, int *in_out_fd, int *files_index);
void		build_commande_env_multiple(t_cmd *data, t_infos *info);
void		is_directory_error(char *commande);
int			is_directory(char *commande);
void		free_int_array(void **array, int size);
void		get_status(int pid, t_infos *infos, int flg);
void		midlle_childs_fails(t_infos *infos, int **pp, int cmd_number);
void		free_allocated_pipes(int **pp, int size);

#endif
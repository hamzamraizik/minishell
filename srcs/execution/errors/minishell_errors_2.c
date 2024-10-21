/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_errors_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochangli <ochangli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 07:05:28 by ochangli          #+#    #+#             */
/*   Updated: 2024/10/17 21:36:18 by ochangli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

/*function exit in case of an error occure when 
reading or writing into a file */
void	no_file_or_dir_exec(char *cmd)
{
	char	*error_string;

	error_string = strerror(errno);
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, error_string, ft_strlen(error_string));
	write(2, "\n", 1);
	if (errno == EACCES)
		exit(126);
	exit(127);
}

/*function exit in case of an error occure when 
reading or writing into a file */
void	commande_not_found_exec(const char *s)
{
	write(2, "minishell : ", 12);
	write(2, s, ft_strlen_exec(s));
	write(2, ": commande not found", 20);
	write(2, "\n", 1);
	exit(NO_SUCH_FILE_OR_DIR);
}

/*This function used to return a permission denied*/
void	permission_denied(char *file_name)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(file_name, 2);
	ft_putstr_fd(": Permission denied\n", 2);
}

/*This function called when the tmp duplicated files fails*/

void	tmp_dup_fails(t_infos	*infos)
{
	perror("dup tmp fds fails:");
	update_exit_status(infos, 1);
}

/*This function called when ambiguous detected*/
void	ambiguous_redirect(t_infos *infos)
{
	ft_putstr_fd("Minishell: ", 2);
	write(2, "ambiguous redirect\n", 19);
	update_exit_status(infos, 1);
	return ;
}

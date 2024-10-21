/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_errors_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochangli <ochangli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:35:57 by ochangli          #+#    #+#             */
/*   Updated: 2024/10/17 14:58:45 by ochangli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

/*This function is called when malloc fails*/
void	malloc_fails(void)
{
	perror("Malloc fails in some point");
	exit(EXIT_FAILURE);
}

/*This function return error in case the file is a directory*/

void	is_directory_error(char *commande)
{
	write(2, "minishell: ", 11);
	write(2, commande, ft_strlen(commande));
	write(2, ": is a directory\n", 17);
	exit(126);
}

void	no_file_or_dir(char	*s)
{
	write(2, "minishell : ", 12);
	write(2, s, ft_strlen_exec(s));
	write(2, ": No such file or directory", 27);
	write(2, "\n", 1);
	exit(NO_SUCH_FILE_OR_DIR);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochangli <ochangli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 15:02:15 by ochangli          #+#    #+#             */
/*   Updated: 2024/10/17 05:32:40 by ochangli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	file_does_not_exist(char *file_name)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(file_name, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

/*This function creat if possible append and outfiles */
int	app_out_creating(char **files, t_files allfiles, int out)
{
	int	fd;

	if (is_exist_in_array(allfiles.appendfiles, files[out]))
		fd = open(files[out], O_CREAT | O_WRONLY, 0644);
	else
		fd = open(files[out], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("minishell :"), 1);
	close(fd);
	return (0);
}

/*This function check if the */
int	delemetre_check(char **files, int out)
{
	if (access(files[out], F_OK))
		return (file_does_not_exist(files[out]), -1);
	else if (access(files[out], R_OK))
		return (permission_denied(files[out]), -1);
	return (0);
}

/*This function is Used to creat all (append , outfiles)*/
int	creat_files(char **files, t_files allfiles, t_infos *infos)
{
	int	out;

	out = 0;
	while (files[out] != NULL)
	{
		if (!is_ambiguous(files[out], allfiles, out))
			return (ambiguous_redirect(infos), -1);
		if (is_exist_in_array(allfiles.appendfiles, files[out])
			|| is_exist_in_array(allfiles.outfiles, files[out]))
		{
			if (app_out_creating(files, allfiles, out) == 1)
				return (update_exit_status(infos, 1), -1);
		}
		else
		{
			if (!is_exist_in_array(allfiles.delemetre, files[out]))
				if (delemetre_check(files, out) == -1)
					return (update_exit_status(infos, 1), -1);
		}
		out++;
	}
	return (0);
}

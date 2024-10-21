/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochangli <ochangli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 15:11:27 by ochangli          #+#    #+#             */
/*   Updated: 2024/10/12 04:46:55 by ochangli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

/*This function used to store the index of The infile and outfile*/
void	init_files_index(t_files	files, int *indexes)
{
	indexes[0] = returned_infile_index(files);
	indexes[1] = returned_outfile_index(files);
}

/*This function only index the array of fds with -1*/
void	init_fds_index(int *fds)
{
	fds[0] = -1;
	fds[1] = -1;
}

/*This function return The index of the last outfile*/
int	returned_outfile_index(t_files	files)
{
	char	**files_array;
	char	**out_files;
	char	**append_files;
	int		index;

	files_array = files.allfiles;
	out_files = files.outfiles;
	append_files = files.appendfiles;
	index = array_lenght(files_array);
	if (--index < 0)
		return (-1);
	while (index >= 0)
	{
		if (get_file_index(files_array[index], out_files) >= 0)
			return (index);
		else if (get_file_index(files_array[index], append_files) >= 0)
			return (index);
		index--;
	}
	return (-1);
}

/*This function return The index of the last infile*/
int	returned_infile_index(t_files files)
{
	char	**files_array;
	char	**in_files;
	char	**her_doc;
	int		index;

	files_array = files.allfiles;
	in_files = files.infiles;
	her_doc = files.delemetre;
	index = array_lenght(files_array);
	if (--index < 0)
		return (-1);
	while (index >= 0)
	{
		if (get_file_index(files_array[index], in_files) >= 0)
			return (index);
		else if (get_file_index(files_array[index], her_doc) >= 0)
			return (index);
		index--;
	}
	return (-1);
}

/*This function checks if there is an infile redirect STDIN ,
    and if there is an outfile redirect STDOUT to it */
int	redirect_commnde(int infile_fd, int outfile_fd)
{
	if (infile_fd >= 0)
	{
		if (dup2(infile_fd, STDIN_FILENO) == -1)
		{
			close(infile_fd);
			return (-1);
		}
		close(infile_fd);
	}
	if (outfile_fd >= 0)
	{
		if (dup2(outfile_fd, STDOUT_FILENO) == -1)
		{
			close(outfile_fd);
			return (-1);
		}
		close(outfile_fd);
	}
	return (0);
}

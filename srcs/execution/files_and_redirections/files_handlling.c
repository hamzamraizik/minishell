/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_handlling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochangli <ochangli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:02:09 by ochangli          #+#    #+#             */
/*   Updated: 2024/10/17 23:15:51 by ochangli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

/*this function creat an fd for the infile to use it in dup
	to read from */
int	open_infile(t_files files, char	*name)
{
	int		fd_infile;
	char	*her_doc_path;

	her_doc_path = ft_strjoin(ft_strdup("/tmp/_"), name);
	fd_infile = -1;
	if (is_exist_in_array(files.infiles, name))
		fd_infile = open(name, O_RDONLY);
	else if (is_exist_in_array(files.delemetre, name))
	{
		fd_infile = open(her_doc_path, O_RDONLY);
		if (fd_infile == -1)
			return (-1);
		unlink(her_doc_path);
	}
	free(her_doc_path);
	return (fd_infile);
}

/*this function creat an fd for the outfile to use it in dup
	to write to */
int	open_outfile(t_files files, char	*name)
{
	int	fd_outfile;

	fd_outfile = -1;
	if (is_exist_in_array(files.outfiles, name))
		fd_outfile = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (is_exist_in_array(files.appendfiles, name))
		fd_outfile = open(name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	return (fd_outfile);
}

/*This function open last outfile and last infile */
int	file_opening(t_cmd	*data, int	*in_out_fd, int	*files_index)
{
	if (files_index[1] >= 0)
	{
		in_out_fd[1] = open_outfile(data->files,
				data->files.allfiles[files_index[1]]);
		if (in_out_fd[1] == -1)
			return (perror("minishell : fails to open outfile: "), 1);
	}
	if (files_index[0] >= 0)
	{
		in_out_fd[0] = open_infile(data->files,
				data->files.allfiles[files_index[0]]);
		if (in_out_fd[0] == -1)
		{
			close(in_out_fd[1]);
			return (perror("fails to open infile"), 1);
		}
	}
	return (0);
}

/*This function creats,open and redirect inputs and outputs*/
int	files_and_redirections(t_cmd	*data, t_infos	*infos)
{
	int	files_index[2];
	int	in_out_fd[2];

	init_files_index(data->files, files_index);
	init_fds_index(in_out_fd);
	if (creat_files(data->files.allfiles, data->files, infos) == -1)
		return (-1);
	if (file_opening(data, in_out_fd, files_index) == -1)
		return (update_exit_status(infos, 1), -1);
	if (redirect_commnde(in_out_fd[0], in_out_fd[1]) == -1)
		return (update_exit_status(infos, 1), -1);
	return (0);
}

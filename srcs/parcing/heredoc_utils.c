/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmraizik <hmraizik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:36:05 by hmraizik          #+#    #+#             */
/*   Updated: 2024/10/16 00:46:22 by hmraizik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_err(void)
{
	ft_putstr_fd("Error: malloc\n", 2);
}

/*if there is a variable in the input entred, and the dilimetre
	not quoted : 'cond' the variable entered will expanded
		else, it will not
*/
void	dil_var_check(char **buffer, int cond, t_infos *infos)
{
	void	*tmp;

	if (*buffer && ft_strchr(*buffer, '$') && cond)
	{
		tmp = *buffer;
		*buffer = handle_var(NULL, 1, infos, *buffer);
		printf("buffer: %s\n", *buffer);
		free(tmp);
	}
}

/* this function is a part of heredoc loop, it works when it's the EOF,
	so all the input are stored in the buffer will writed in a tmp file,
		and if it's not the last heredoc in the cmd, it will unlinked
*/
int	write_in_file(int ifd[], char *dilimetre, char **buffer, char *line)
{
	char	*file_name;
	int		flag;

	file_name = NULL;
	file_name = ft_strjoin(ft_strdup("/tmp/_"), dilimetre);
	if (!file_name)
		return (1);
	flag = ifd[1];
	ifd[1] = open(file_name, O_WRONLY | O_CREAT, 0644);
	if (ifd[1] < 0)
		return (free(file_name), 1);
	ft_putstr_fd(*buffer, ifd[1]);
	if (line)
		free(line);
	free(*buffer);
	close(ifd[1]);
	if (flag != -1)
		unlink(file_name);
	free(file_name);
	return (0);
}

/*this function remove the quotes from the delemetre array
	after the heredoc process ended, it not removed before because
		it needed in heredoc process to check if the input variables 
			should expanded or not, if the dilimetre quoted so no expansion
*/
int	update_heredoc_files(t_files *files)
{
	int		i;
	char	*tmp;

	i = 0;
	while (files->delemetre && files->delemetre[i])
	{
		tmp = files->delemetre[i];
		files->delemetre[i] = trim_name_quotes(files->delemetre[i], IN);
		free(tmp);
		i++;
	}
	return (0);
}

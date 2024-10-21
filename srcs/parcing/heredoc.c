/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmraizik <hmraizik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:49:16 by hmraizik          #+#    #+#             */
/*   Updated: 2024/10/17 05:45:22 by hmraizik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*this function parse the dilimetre, wich is the EOF:
	removing quotes, handle the '$' sign
*/
char	*parse_dilimetre(char *s)
{
	int		i;
	int		j;
	int		is_quote;
	char	*new;

	initial_ints(&i, &j, &is_quote);
	new = malloc(ft_strlen(s) + 1 * sizeof(char));
	if (!new)
		return (NULL);
	while (s[i])
	{
		is_quote = check_quotes(is_quote, s[i]);
		if (!is_quote && s[i] == '$' && s[i + 1] == '$')
		{
			new[j++] = s[i++];
			is_quote = check_quotes(is_quote, s[i]);
			new[j++] = s[i++];
		}
		else
			new[j++] = s[i++];
	}
	return (new[j] = '\0', new = trim_quotes(new), new);
}

/*this function is a part of the loop of collecting the input,
	it check if it's the end of file, then it write the buffer in a file,
		else , it still collect input and store it in a buffer until it find EOF
*/
int	collect_input2(char **buffer, char *dilimetre, int ifd[], t_infos *infos)
{
	char	*line;
	char	*tmp_buffer;

	line = readline("» ");
	if (!line || !ft_strncmp(line, dilimetre
			, ft_strlen(dilimetre) + 1) || g_signal == 1)
	{
		if (write_in_file(ifd, dilimetre, buffer, line))
			return (1);
		return (0);
	}
	tmp_buffer = ft_strjoin(line, "\n");
	if (!tmp_buffer)
		return (close(ifd[1]), free(*buffer), put_err(), 1);
	dil_var_check(&tmp_buffer, ifd[3], infos);
	*buffer = ft_strjoin(*buffer, tmp_buffer);
	if (!*buffer)
		return (close(ifd[1]), free(tmp_buffer), put_err(), 1);
	free(tmp_buffer);
	return (2);
}

/* this function is a part of here-doc, it start an infinit
	loop until find the EOF, in the loop it collect any input,
		that will be stored in a file in the fuction collect_input2()
*/
int	collect_input(char **buffer, char *dilimetre, int ifd[], t_infos *infos)
{
	char	*line;
	int		returned_value;

	line = NULL;
	*buffer = NULL;
	while (1)
	{
		if (g_signal == 1 && printf("\n"))
		{
			infos->exit_status = 1;
			break ;
		}
		returned_value = collect_input2(buffer, dilimetre, ifd, infos);
		if (returned_value == 0)
			break ;
		if (returned_value == 1)
			return (1);
		else if (returned_value == 2)
			continue ;
	}
	return (0);
}

/* this function loop on all heredocs in the cmd,
	and for each one it parse the dilimetre and start
	another loop to collect the input that will stored
	in a file later
*/
int	start_heredoc(t_files *files, int ifd[], t_infos *infos)
{
	char	*buffer;
	char	*dilimitre;

	(signal(SIGINT, sig_hedroc), rl_catch_signals = 1);
	signal(SIGQUIT, SIG_IGN);
	while (files->delemetre[ifd[0]] && g_signal == 0)
	{
		ifd[3] = (!ft_strchr(files->delemetre[ifd[0]], '\'')
				&& !ft_strchr(files->delemetre[ifd[0]], '\"'));
		dilimitre = parse_dilimetre((files->delemetre[ifd[0]]));
		if (!files->delemetre[ifd[0] + 1])
			ifd[1] = -1;
		if (collect_input(&buffer, dilimitre, ifd, infos))
			return (1);
		free(dilimitre);
		(ifd[0])++;
	}
	signals();
	return (0);
}

/* this function is the main function of the heredoc
	it loop over all the cmds and calls the start_heredoc()
	function for each cmd
*/
int	ft_heredoc(t_cmd *cmd, t_infos *infos)
{
	int		ifd[4];
	t_files	files;

	ifd[2] = dup(0);
	while (cmd)
	{
		ifd[0] = 0;
		files = cmd->files;
		if (files.delemetre && files.delemetre[ifd[0]])
			start_heredoc(&files, ifd, infos);
		cmd = cmd->next;
	}
	dup2(ifd[2], 0);
	close(ifd[2]);
	update_heredoc_files(&files);
	return (0);
}

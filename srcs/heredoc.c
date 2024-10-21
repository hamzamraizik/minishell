#include "../includes/minishell.h"

char    *remove_quotes(char *s)
{
	int     i;
	int     j;
	char    *new;

	i = 0;
	j = 0;
	new = malloc(ft_strlen(s) + 1 * sizeof(char));
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			i++;
		else
			new[j++] = s[i++];
	}
	new[j] = '\0';
	return (new);
}

void    sig_hedroc(int signo)
{
	(void)signo;
	g_signal = 1;
	close(0);
}

void    ft_heredoc(t_cmd *cmd)
{
	int     ifd[2]; //array of ints just for norm
	static  int idx; // hold the index of the file
	char    *line;
	char    *leak;
	char    *buffer;
	char    *file_name;
	int	second;
	t_files files;
	bool    cond;

	second = dup(0);
	signal(SIGINT, sig_hedroc);
	while (cmd)
	{
		ifd[0] = 0;
		files = cmd->files;
		if (files.delemetre && files.delemetre[0])
		{
			cond = (!ft_strchr(files.delemetre[ifd[0]], '\'')// if it contain quotes
					&& !ft_strchr(files.delemetre[ifd[0]], '\"'));
			//remove any quotes from the delemetre
			files.delemetre[0] = remove_quotes(files.delemetre[0]);
			while (files.delemetre[ifd[0]] && g_signal == 0)
			{
				buffer = NULL;
				leak = ft_itoa(idx++);
				if (!leak)
					return(ft_putstr_fd("Error: malloc\n", 2));
				file_name = ft_strjoin(ft_strdup("/tmp/"), leak);
				free(leak);
				ifd[1] = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (ifd[1] < 0)
					return(ft_putstr_fd("Error: open\n", 2));
				while (1)
				{
					if (g_signal == 1)
					{
						printf("\n");
						close(ifd[1]);
						unlink(file_name);
						break;
					}
					line = readline("> ");
					if (!line || !ft_strncmp(line, files.delemetre[ifd[0]]
						, ft_strlen(files.delemetre[ifd[0]]) + 1) || g_signal == 1)
					{
						free(line);
						close(ifd[1]);
						break;
					}
					buffer = ft_strjoin(buffer, line);
					if (!buffer)
						return (close(ifd[1]), free(line), ft_putstr_fd("Error: malloc\n", 2));
					buffer = ft_strjoin(buffer, "\n");
					if (!buffer)
						return(close(ifd[1]),free(line), ft_putstr_fd("Error: malloc\n", 2));
					free(line);
				}
				if (buffer && ft_strchr(buffer, '$') && cond)
					buffer = handle_var(buffer);
				ft_putstr_fd(buffer, ifd[1]);
				free(file_name);
				free(buffer);
				close(ifd[1]);
				ifd[0]++;
			}
		}
		cmd = cmd->next;
	}
	dup2(second, 0);
	close(second);
	g_signal = 0;
	signals();
}
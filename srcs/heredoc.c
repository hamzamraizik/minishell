#include "../includes/minishell.h"

void    ft_heredoc(t_cmd *cmd)
{
    int ifd[2];
    static int idx;
    char *line;
    char    *leak;
    char    *buffer;
    char *file_name;
    t_files files;

    while (cmd)
    {
        ifd[0] = 0;
        files = cmd->files;
        if (files.delemetre && files.delemetre[0])
        {
            while (files.delemetre[ifd[0]])
            {
                buffer = NULL;
                leak = ft_itoa(idx++);
                if (!leak)
                    return(ft_putstr_fd("Error: malloc 1\n", 2));
                file_name = ft_strjoin(ft_strdup("/tmp/"), leak);
                free(leak);
                ifd[1] = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (ifd[1] < 0)
                    return(ft_putstr_fd("Error: open 2\n", 2));
                free(file_name);
                while (1)
                {
                    line = readline("> ");
                    if (!line || !ft_strncmp(line, files.delemetre[ifd[0]], ft_strlen(files.delemetre[ifd[0]]) + 1))
                    {
                        free(line);
                        close(ifd[1]);
                        break;
                    }
                    buffer = ft_strjoin(buffer, line);
                    if (!buffer)
                        return (close(ifd[1]), free(line), ft_putstr_fd("Error: malloc 3\n", 2));
                    buffer = ft_strjoin(buffer, "\n");
                    if (!buffer)
                        return(close(ifd[1]),free(line), ft_putstr_fd("Error: malloc 2\n", 2));
                    free(line);
                }
                ft_putstr_fd(buffer, ifd[1]);
                free(buffer);
                close(ifd[1]);
                ifd[0]++;
            }
        }
        cmd = cmd->next;
    }
}


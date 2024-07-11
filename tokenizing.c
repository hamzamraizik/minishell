#include "minishell.h"

void	tokenizing(t_list **head, char **line)
{
    int	i;

	i = 0;
    while (line[i]) {
        if (strcmp(line[i], "|") == 0)
            list_add_back(head, creat_node("|", PIPE));
        else if (strcmp(line[i],"<") == 0)
            list_add_back(head, creat_node("<", IN));
        else if (strcmp(line[i],">") == 0)
            list_add_back(head, creat_node(">", OUT));
        else if (strcmp(line[i],";") == 0)
            list_add_back(head, creat_node(";", SEMI));
		else if (strcmp(line[i]," ") == 0)
            list_add_back(head, creat_node(" ", T_SPACE));
        else
        	list_add_back(head, creat_node(line[i], WORD));
        i++;
    }
}

char *add_delimetre(char *line)
{
    int		i;
    int		is_quotes;

    i = 0;
    is_quotes = 0;
    while (line[i])
    {
        if (is_quotes == 0 && line[i] == '\'')
            is_quotes = 1;
        else if (is_quotes == 0 && line[i] == '\"')
            is_quotes = 2;
        else if (is_quotes == 1 && line[i] == '\'')
            is_quotes = 0;
        else if (is_quotes == 2 && line[i] == '\"')
            is_quotes = 0;

        if (is_quotes == 0 && line[i] == ' ')
        {
            line[i] = '\0';
            while(line[i + 1] == ' ' || line[i + 1] == '\t')
                i++;
        }
        i++;
    }
    return (line);
}

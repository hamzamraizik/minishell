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

char	*parse_line(char *line, int length)
{
	char **new_line;
	t_list	*head;

	length = ft_strlen(line);
	line = add_delimetre(line);
	new_line = ft_new_split(line, '\0', length);
	head = NULL;
	tokenizing(&head, new_line);
	while(head != NULL)
	{
		printf("%s\n", head->content);
		head = head->next;
	}
	return line;
}

int main(int argc, char **argv, char **envp)
{
	char	*line;
	int		line_length;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		line = readline(GRN"write a prompt: ");
		if (check_if_empty(line))
		{
			free(line);
			continue ;
		}
		// handle syntax error cases.
		add_history(line);
		line_length = ft_strlen(line);
		line = parse_line(line, line_length);
	}
}

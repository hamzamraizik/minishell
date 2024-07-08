#include "minishell.h"

// void tokenizing(t_list **head, char *line)
// {
// 	int		i;

// 	i = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == '|')
// 			list_add_back(head, creat_node("|", PIPE));
// 		else if (line[i] == '<')
// 			list_add_back(head, creat_node("<", IN));
// 		else if (line[i] == '>')
// 			list_add_back(head, creat_node(">", OUT));
// 		else if (line[i] == ';')
// 			list_add_back(head, creat_node(";", SEMI));
// 		else if (line[i] == ' ')
// 			list_add_back(head, creat_node(" ", SPACE));
// 		else if (line[i] == '\n')
// 			list_add_back(head, creat_node("\n", NEWLINE));
// 		else
// 		{
// 			// add word to the list
// 			// while (line[i] && line[i] != '|' && line[i] != '<' && line[i] != '>' && line[i] != ';' && line[i] != ' ' && line[i] != '\n')
// 			// 	i++;
// 			// list_add_back(head, creat_node("word", WORD));
// 		}
// 	}
// }


// hello "hii 'aa'bb' hoo" world


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
            line[i] = 26;
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

	//add spaces before and after the special characters, for splitting the line into tokens.
	int i = 0;
	(void)length;
	line = add_delimetre(line);
	head = NULL;
	new_line = ft_split(line, 26);
	while(new_line[i] != NULL)
	{
		list_add_back(&head, creat_node(new_line[i], WORD));
		i++;
	}
	while(head != NULL)
	{
		printf("%s\n", head->content);
		head = head->next;
	}
	return line;
	//parse the line into tokens.
	// tokenizing(&head, line);
}

int main(int argc, char **argv, char **envp)
{
	char	*line;
	int		line_length;
	// char **args;
	// int status;
	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		// dup(1);
		// printf(GRN"minishell> ");
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
		// int i = 0;
		// while(i < line_length + 1)
		// {
		// 	if (line[i] == '\0')
		// 		write(1, "X", 1);
		// 	else
		// 		write(1, &line[i], 1);
		// 	i++;
		// }
	}
}

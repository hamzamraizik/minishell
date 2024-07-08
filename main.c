#include "minishell.h"

void tokenizing(t_list **head, char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '|')
			list_add_back(head, creat_node("|", PIPE));
		else if (line[i] == '<')
			list_add_back(head, creat_node("<", IN));
		else if (line[i] == '>')
			list_add_back(head, creat_node(">", OUT));
		else if (line[i] == ';')
			list_add_back(head, creat_node(";", SEMI));
		else if (line[i] == ' ')
			list_add_back(head, creat_node(" ", SPACE));
		else if (line[i] == '\n')
			list_add_back(head, creat_node("\n", NEWLINE));
		else
		{
			while (line[i] && line[i] != '|' && line[i] != '<' && line[i] != '>' && line[i] != ';' && line[i] != ' ' && line[i] != '\n')
				i++;
			list_add_back(head, creat_node("word", WORD));
		}
	}
}

void	parse_line(char *line)
{
	t_list	*head;

	tokenizing(&head, line);
}
int main(int argc, char **argv, char **envp)
{
	char *line;
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
		parse_line(line);
		// parse_line(line);
	}
}

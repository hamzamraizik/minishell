#include "minishell.h"

void	tokenizing(t_list **head, char **line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (strncmp(line[i], "|", 1) == 0)
			list_add_back(head, creat_node(line[i], PIPE));
		else if (strncmp(line[i],"<<", 2) == 0)
			list_add_back(head, creat_node(line[i], HEREDOC));
		else if (strncmp(line[i],"<", 1) == 0)
			list_add_back(head, creat_node(line[i], IN));
		else if (strncmp(line[i],">>", 2) == 0)
			list_add_back(head, creat_node(line[i], APPEND));
		else if (strncmp(line[i],">", 1) == 0)
			list_add_back(head, creat_node(line[i], OUT));
		else if (get_last_node(*head) && get_last_node(*head)->type == HEREDOC)
			list_add_back(head, creat_node(line[i], DELEMETRE));
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
		is_quotes = check_quotes(is_quotes, line[i]);
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

#include "minishell.h"

int check_if_empty(char *line)
{
	int i;

	i = 0;
	if (line[i] == '\0')
		return (1);
	while (line[i] == ' ')
		i++;
	if (!line[i])
		return (1);
	return (0);
}

void    *creat_node(char *content, int type)
{
	t_list *node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->type = type;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void    list_add_back(t_list **head, t_list *new)
{
	t_list *last;

	if (!*head)
	{
		*head = new;
		return ;
	}
	last = *head;
	while (last->next)
		last = last->next;
	last->next = new;
	new->prev = last;
}

int	check_special(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == ';' || c == '$')
		return (1);
	else
		return (0);
}
int	check_quotes(int is_quotes, char c)
{
	if (is_quotes == 0 && c == '\'')
			is_quotes = 1;
	else if (is_quotes == 0 && c == '\"')
		is_quotes = 2;
	else if (is_quotes == 1 && c == '\'')
		is_quotes = 0;
	else if (is_quotes == 2 && c == '\"')
		is_quotes = 0;
	return(is_quotes);
}

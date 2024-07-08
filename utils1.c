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

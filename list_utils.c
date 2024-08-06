#include "minishell.h"

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

void	*lstclear(t_list *tmp)
{
	t_list *tmp2;
	while (tmp)
	{
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2);
	}
	return (NULL);
}

t_list  *get_last_node(t_list *head)
{
	t_list *last;

	last = head;
	if (!last)
		return (NULL);
	while (last->next)
		last = last->next;
	return (last);
}

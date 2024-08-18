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

t_cmd *new_cmd_node(void)
{
    t_cmd *new_node;

    new_node = (t_cmd *)malloc(sizeof(t_cmd));
    if (!new_node)
        return (NULL);
    new_node->cmd = NULL;
    new_node->next = NULL;
    return (new_node);
}

void	cmd_add_back(t_cmd **head, t_cmd *new)
{
	t_cmd	*last;

	if (!new)
		return ;
	if (!(*head))
	{
		*head = new;
		return ;
	}
	last = *head;
	while (last && last->next)
		last = last->next;
	last->next = new;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmraizik <hmraizik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 23:30:52 by hmraizik          #+#    #+#             */
/*   Updated: 2024/10/16 23:30:53 by hmraizik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*creat_node(char *content, int type)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->type = type;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

int	list_add_back(t_list **head, t_list *new)
{
	t_list	*last;

	if (!new)
		return (1);
	if (!*head)
	{
		*head = new;
		return (0);
	}
	last = *head;
	while (last->next)
		last = last->next;
	last->next = new;
	new->prev = last;
	return (0);
}

void	clear_lst_content(t_list **tmp)
{
	t_list	*tmp2;

	while (*tmp)
	{
		tmp2 = *tmp;
		*tmp = ((*tmp)->next);
		free(tmp2->content);
		free(tmp2);
	}
	return ;
}

void	lstclear(t_list **tmp)
{
	t_list	*tmp2;

	clear_lst_content(tmp);
	while (tmp && *tmp)
	{
		tmp2 = *tmp;
		*tmp = ((*tmp)->next);
		free(tmp2);
		tmp2 = NULL;
	}
	return ;
}

t_list	*get_last_node(t_list *head)
{
	t_list	*last;

	last = head;
	if (!last)
		return (NULL);
	while (last->next)
		last = last->next;
	return (last);
}

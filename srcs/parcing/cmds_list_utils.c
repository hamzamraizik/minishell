/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_list_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmraizik <hmraizik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:48:46 by hmraizik          #+#    #+#             */
/*   Updated: 2024/10/01 12:57:42 by hmraizik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd_node(void)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->cmd = NULL;
	new_node->files.infiles = NULL;
	new_node->files.outfiles = NULL;
	new_node->files.appendfiles = NULL;
	new_node->files.delemetre = NULL;
	new_node->files.allfiles = NULL;
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

int	count_var_words( char *s, char c)
{
	int	count;
	int	c_fond;

	count = 1;
	c_fond = 0;
	while (*s)
	{
		if (*s == c)
			c_fond = 0;
		else if (!c_fond && *s != c)
		{
			c_fond = 1;
			count++;
		}
		s++;
	}
	return (count);
}

int	count_cmds(t_list *head)
{
	int		count;
	t_list	*last;

	count = 0;
	last = head;
	while (head && head->type != PIPE)
	{
		if ((head->type == WORD || head->type == VAR
				|| head->type == NORMAL_VAR)
			&& (last && (last->type == WORD || last->type == VAR
					|| last->type == NORMAL_VAR || last->type == DELEMETRE)))
		{
			if (head->type == NORMAL_VAR)
				count += count_var_words(head->content, ' ');
			else
				count += 1;
		}
		last = head;
		head = head->next;
	}
	return (count);
}

int	count_type(t_list *head, int type)
{
	int	count;

	count = 0;
	while (head && head->type != PIPE)
	{
		if (head->type == type)
			count++;
		head = head->next;
	}
	return (count);
}

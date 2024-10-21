/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_list_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmraizik <hmraizik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:55:48 by hmraizik          #+#    #+#             */
/*   Updated: 2024/10/16 23:25:17 by hmraizik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_filles_prt2(t_list *head, t_files *files, int *index)
{
	if (head && head->type == DELEMETRE)
		files->delemetre[index[3]++] = ft_strdup(head->content);
	if ((head->type == IN || head->type == OUT || head->type == APPEND)
		&& head->next && (head->next->type == WORD || head->next->type == VAR
			|| head->next->type == NORMAL_VAR))
	{
		if ((head->type == IN || head->type == OUT || head->type == APPEND)
			&& head->next && head->next->type == NORMAL_VAR
			&& (head->next->content[0] == '\0'
				|| is_contain_spaces(head->next->content)))
			files->ambiguous_indexes[index[5]++] = index[4];
		files->allfiles[index[4]++] = trim_name_quotes
			(head->next->content, head->next->type);
	}
	else if (head->type == DELEMETRE)
		files->allfiles[index[4]++] = trim_name_quotes
			(head->content, DELEMETRE);
}

void	free_cmds(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd->cmd[i])
	{
		free(cmd->cmd[i]);
		cmd->cmd[i] = NULL;
		i++;
	}
}

void	clear_cmds_list(t_cmd **cmd_list)
{
	t_cmd	*tmp;
	t_cmd	*head;

	head = *cmd_list;
	while (head)
	{
		tmp = head;
		head = (head)->next;
		free_files(&tmp->files);
		free_cmds(tmp);
		free(tmp->cmd);
		free(tmp->files.infiles);
		tmp->files.infiles = NULL;
		free(tmp->files.outfiles);
		tmp->files.outfiles = NULL;
		free(tmp->files.appendfiles);
		tmp->files.appendfiles = NULL;
		free(tmp->files.delemetre);
		tmp->files.delemetre = NULL;
		free(tmp->files.allfiles);
		tmp->files.allfiles = NULL;
		free(tmp->files.ambiguous_indexes);
		free(tmp);
		tmp = NULL;
	}
}

int	allfiles_counter(t_list *head)
{
	return ((count_type(head, IN) + count_type(head, OUT)
			+ count_type(head, APPEND) + count_type(head, DELEMETRE)
			+ 1));
}

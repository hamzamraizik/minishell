/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_list_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmraizik <hmraizik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:48:41 by hmraizik          #+#    #+#             */
/*   Updated: 2024/10/17 07:16:08 by hmraizik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parse_the_cmd(t_list *tmp, char **cmds, int *i)
{
	char	**tmp2 ;
	int		j;

	j = 0;
	if (tmp->type == NORMAL_VAR && tmp->content && is_empty(tmp->content))
		return (0);
	if (tmp->type == NORMAL_VAR && ft_strchr(tmp->content, ' '))
	{
		tmp2 = ft_split(tmp->content, ' ');
		if (!tmp2)
			return (1);
		while (tmp2 && tmp2[j])
			cmds[(*i)++] = tmp2[j++];
		free(tmp2);
	}
	else
	{
		if (fill_cmd(tmp, &cmds[(*i)++]))
			return (1);
	}
	return (0);
}

char	**fill_cmds_array(t_list *head)
{
	char	**cmds;
	t_list	*tmp;
	t_list	*last;
	int		i;

	i = 0;
	tmp = head;
	cmds = malloc((count_cmds(head) + 1) * sizeof(char *));
	if (!cmds)
		return (NULL);
	last = tmp;
	while (tmp && tmp->type != PIPE)
	{
		if ((tmp->type == WORD || tmp->type == VAR || tmp->type == NORMAL_VAR)
			&& (last && (last->type == WORD || last->type == VAR
					|| last->type == NORMAL_VAR || last->type == DELEMETRE)))
			if (ft_parse_the_cmd(tmp, cmds, &i))
				return (NULL);
		last = tmp;
		tmp = tmp->next;
	}
	cmds[i] = NULL;
	return (cmds);
}

int	allocate_args(t_list *head, t_files *files)
{
	files->infiles = malloc((count_type(head, IN) + 1) * sizeof(char *));
	if (!files->infiles)
		return (1);
	files->outfiles = malloc((count_type(head, OUT) + 1)
			* sizeof(char *));
	if (!files->outfiles)
		return (free(files->infiles), 1);
	files->appendfiles = malloc((count_type(head, APPEND) + 1)
			* sizeof(char *));
	if (!files->appendfiles)
		return (free(files->infiles), free(files->outfiles), 1);
	files->delemetre = malloc((count_type(head, DELEMETRE) + 1)
			* sizeof(char *));
	if (!files->delemetre)
		return (free(files->infiles), free(files->outfiles),
			free(files->appendfiles), 1);
	files->allfiles = malloc(allfiles_counter(head) * sizeof(char *));
	if (!files->allfiles)
		return (free(files->infiles), free(files->outfiles),
			free(files->appendfiles), free(files->delemetre), 1);
	files->ambiguous_indexes = malloc(allfiles_counter(head) * sizeof(int));
	return (0);
}

t_files	fill_files(t_list *head)
{
	t_files		files;
	int			index[6];

	if (allocate_args(head, &files))
		return (files);
	initial_ints(&index[0], &index[1], &index[2]);
	initial_ints(&index[3], &index[4], &index[5]);
	while (head && head->type != PIPE)
	{
		if (head->type == IN && head->next && (head->next->type == WORD
				|| head->next->type == VAR || head->next->type == NORMAL_VAR))
			files.infiles[index[0]++] = trim_name_quotes(head->next->content,
					head->next->type);
		if (head->type == OUT && head->next && (head->next->type == WORD
				|| head->next->type == VAR || head->next->type == NORMAL_VAR))
			files.outfiles[index[1]++] = trim_name_quotes
				(head->next->content, head->next->type);
		if (head->type == APPEND && head->next && (head->next->type == WORD
				|| head->next->type == VAR || head->next->type == NORMAL_VAR))
			files.appendfiles[index[2]++] = trim_name_quotes
				(head->next->content, head->next->type);
		fill_filles_prt2(head, &files, index);
		head = head->next;
	}
	return (terminate_files(&files, index), files);
}

t_cmd	*fill_cmds_list(t_list **head)
{
	t_cmd	*cmds;
	t_list	*tmp;
	t_cmd	*tmp_cmd;

	tmp = *head;
	cmds = NULL;
	while (tmp)
	{
		tmp_cmd = new_cmd_node();
		if (!tmp_cmd)
			return (NULL);
		tmp_cmd->cmd = fill_cmds_array(tmp);
		if (!tmp_cmd->cmd)
			return (NULL);
		tmp_cmd->files = fill_files(tmp);
		while (tmp && tmp->type != PIPE)
			tmp = tmp->next;
		if (tmp && tmp->type == PIPE)
			tmp = tmp->next;
		cmd_add_back(&cmds, tmp_cmd);
	}
	cmds->head = *head;
	return (cmds);
}

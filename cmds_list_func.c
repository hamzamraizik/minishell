#include "minishell.h"


int count_cmds(t_list *head)
{
	int count;

	count = 0;
	while (head && head->type != PIPE)
	{
		count++;
		head = head->next;
	}
	return (count);
}

char	**fill_cmds_array(t_list *head)
{
	char	**cmds;
	int		cmds_count;
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = head;
	cmds_count = count_cmds(head);
	cmds = malloc(cmds_count + 1);
	if (!cmds)
		return (NULL);
	while (tmp && tmp->type != PIPE)
	{
		cmds[i] = tmp->content;
		tmp = tmp->next;
		i++;
	}
	cmds[i] = NULL;
	return (cmds);
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

void	allocate_args(t_list *head ,t_files *files)
{
	files->infiles = malloc(count_type(head, IN) + 1);
	if (!files->infiles)
		return ;
	files->outfiles = malloc(count_type(head, OUT) + 1);
	if (!files->outfiles)
		return ;
	files->appendfiles = malloc(count_type(head, APPEND) + 1);
	if (!files->appendfiles)
		return ;
	files->delemetre = malloc(count_type(head, DELEMETRE) + 1);
	if (!files->delemetre)
		return ;
}

t_files	fill_files(t_list *head)
{
	t_files	files;
	int		index[4];

	allocate_args(head, &files);
	initial_ints(&index[0], &index[1], &index[2]);
	index[3] = 0;
	while (head && head->type != PIPE)
	{
		if (head->type == IN && head->next && head->next->type == WORD)
			files.infiles[index[0]++] = head->next->content;
		if (head->type == OUT && head->next && head->next->type == WORD)
			files.outfiles[index[1]++] = head->next->content;
		if (head->type == APPEND && head->next && head->next->type == WORD)
			files.appendfiles[index[2]++] = head->next->content;
		if (head->type == DELEMETRE)
			files.delemetre[index[3]++] = head->content;
		head = head->next;
	}
	files.infiles[index[0]] = NULL;
	files.outfiles[index[1]] = NULL;
	files.appendfiles[index[2]] = NULL;
	files.delemetre[index[3]] = NULL;
	return (files);
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
		tmp_cmd->cmd = fill_cmds_array(tmp);
		tmp_cmd->files = fill_files(tmp);
		while (tmp && tmp->type != PIPE)
			tmp = tmp->next;
		if (tmp && tmp->type == PIPE)
			tmp = tmp->next;
		cmd_add_back(&cmds, tmp_cmd);
	}
	return (cmds);
}
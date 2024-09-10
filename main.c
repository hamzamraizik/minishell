#include "minishell.h"

int check_multi_pipes(char *line)
{
	int	i;

	i = 0;
	while(line[i])
	{
		if ((line[i] == '|' && line[i + 1] == '|' && line[i+2] == '|') ||
				(line[i] == '|' && line[i + 1] == ' ' && line[i + 2] == '|'))
			return (1);
		i++;
	}
	return (0);
}

int in_out_check(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if ((line[i] == '<' && line[i + 1] != '<' && check_special(line[i + 1]))
			|| (line[i] == '<' && (line[i + 1] == '<' || line[i + 1] == ' ') && line[i + 2] == '<'))
			return (1);
		if ((line[i] == '>' && line[i + 1] != '>' && check_special(line[i + 1]))
			|| (line[i] == '>' && (line[i + 1] == '>' || line[i + 1] == ' ')
				 && line[i + 2] == '>'))
			return (1);
		i++;
	}
	return (0);
}

int	first_syntax_check(char *line)
{
	int		is_quotes;
	int		i;

	is_quotes = i = 0;
	while (line[i])
		is_quotes = check_quotes(is_quotes, line[i++]);
	if (is_quotes == 1 || is_quotes == 2)
		return (printf("mini_hell: syntax_error, quotes not closed\n"), 1);
	if (line && (line[0] == '|' || line[ft_strlen(line) - 1] == '|'))
		return (printf("mini_hell: syntax error near unexpected token `|'\n"), 1);
	if (check_multi_pipes(line))
		return (printf("mini_hell: syntax error near unexpected token `|'\n"), 1);
	if (in_out_check(line))
		return (printf("mini_hell: syntax error\n"), 1);
	return 0;
}

int	count_new_len(char *line, int old_len)
{
	int	i;

	i = 0;
	while(line[i])
	{
		if (check_special(line[i]))
				old_len += 2;
		i++;
	}
	return (old_len);
}
char	**free_substrs(char **substrs)
{
	int	i;

	i = 0;
	while (substrs && substrs[i])
		free(substrs[i++]);
	if (substrs)
		free(substrs);
	return (NULL);
}

void	parse_line(char *line, t_list	**head, int length)
{
	char	**new_line;

	*head = NULL;
	new_line = NULL;
	if (!line)
		return;
	line = add_delimetre(line, length);
	new_line = ft_new_split(line, '\0', length);
	if (!new_line)
		return ;
	tokenizing(head, new_line);
	free(new_line);
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
		free(tmp->cmd);
		free(tmp->files.infiles);
		free(tmp->files.outfiles);
		free(tmp->files.appendfiles);
		free(tmp->files.delemetre);
		free(tmp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char    *new_line;
	t_list	*head;
	t_cmd	*cmd_list;
	// int		i;

	// i = 0;
	(void)argc;
	(void)argv;
	(void)envp;
	head = NULL;
	while (1)
	{
		line = readline("Minishell -> ");
		if (!line)
			return (1);
		if (check_if_empty(line) || first_syntax_check(line))
		{
			free(line);
			continue ;
		}
		 if (*line)
			add_history(line);
		new_line = add_spaces(line, count_new_len(line, ft_strlen(line)));
		parse_line(new_line, &head, ft_strlen(new_line));
		if (syntax_error(head) == 1)
		{
			printf("mini_hell: syntax error\n");
			lstclear(&head);
			continue ;
		}
		expanding(&head);
		cmd_list = fill_cmds_list(&head);
		// t_cmd *tmpp = cmd_list;
		t_list *tmp  = head;
		while (tmp)
		{
			printf("%s =====>	%s\n", tmp->content, tmp->type == 1 ? "PIPE" : 
				tmp->type == 2 ? "HEREDOC" : tmp->type == 3 ? "APPEND" : tmp->type == 5 ? "IN" : 
					tmp->type == 6 ? "OUT" : tmp->type == 12 ? "DELEMETRE" : tmp->type == 4 ? "VAR" : "WORD");
			tmp = tmp->next;
		}
		free(new_line);
		lstclear(&head);
		clear_cmds_list(&cmd_list);
	}
}

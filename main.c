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
		if(check_special(line[i]) && line[i + 1] != ' ')
				old_len += 2;
		i++;
	}
	return (old_len);
}

void	parse_line(char *line, t_list	**head, int length)
{
	char	**new_line;

	*head = NULL;
	line = add_delimetre(line);// replace space with '\0' for splite
	new_line = ft_new_split(line, '\0', length); // splite line with '\0'
	tokenizing(head, new_line); // listing it into tokenz
	free(new_line); // not freing substers because the same adresses uses in list
	return ;
}

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

char **fill_cmds_array(t_list *head)
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

t_cmd	*fill_cmds_list(t_list **head)
{
	t_cmd	*cmds;
	t_list	*tmp;
	t_cmd	*tmp_cmd;

	tmp = *head;
	while (tmp)
	{
		tmp_cmd = new_cmd_node();
		tmp_cmd->cmd = fill_cmds_array(tmp);
		while (tmp && tmp->type != PIPE)
			tmp = tmp->next;
		if (tmp && tmp->type == PIPE)
			tmp = tmp->next;
		cmd_add_back(&cmds, tmp_cmd);
	}
	return (cmds);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char    *new_line;
	t_list	*head;
	t_cmd	*cmd_list;
	int		i;

	// i = 0;
	(void)argc;
	(void)argv;
	(void)envp;
	head = NULL;
	while (1)
	{
		 line = readline("Minishell -> ");
		 if(*line)
			add_history(line);
		if (check_if_empty(line) || first_syntax_check(line))
			continue ;
		new_line = add_spaces(line, count_new_len(line, ft_strlen(line)));// add spaces before special symbols to splite it after
		parse_line(new_line, &head, ft_strlen(new_line));
		if (syntax_error(head) == 1 && !lstclear(head))
			continue ;
		expanding(&head);
		cmd_list = fill_cmds_list(&head);
		(void)cmd_list;
		while (cmd_list)
		{
			i = 0;
			puts("____________________\n");
			while(cmd_list->cmd[i])
			{
				printf("%s\n", cmd_list->cmd[i]);
				i++;
			}
			cmd_list = cmd_list->next;
		}
		// while(head != NULL)
		// {
		// 	printf("%s =====>	%s\n", head->content, head->type == 1 ? "PIPE" : 
		// 		head->type == 2 ? "HEREDOC" : head->type == 3 ? "APPEND" : head->type == 5 ? "IN" : 
		// 			head->type == 6 ? "OUT" : head->type == 12 ? "DELEMETRE" : "WORD");
		// 	head = head->next;
		// }
		// lstclear(head);
		free(new_line);
	}
}

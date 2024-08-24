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
void	free_substrs(char **substrs)
{
	int	i;

	i = 0;
	while (substrs && substrs[i])
		free(substrs[i++]);
	if (substrs)
		free(substrs);
	return ;
}

void	parse_line(char *line, t_list	**head, int length)
{
	char	**new_line;

	*head = NULL;
	new_line = NULL;
	line = add_delimetre(line);// replace spaces with '\0' for splite
	new_line = ft_new_split(line, '\0', length); // splite line with '\0'
	tokenizing(head, new_line); // listing it into tokenz
	free(new_line); // not freing substers because the same adresses uses in list
	return ;
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
		free(tmp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char    *new_line;
	t_list	*head;
	t_cmd	*cmd_list;
	int		i;

	i = 0;
	(void)argc;
	(void)argv;
	(void)envp;
	head = NULL;
	while (1)
	{
		 line = readline("Minishell -> ");
		if (!line)
			return (1);
		 if (*line)
			add_history(line);
		if (check_if_empty(line) || first_syntax_check(line))
		{
			free(line);
			continue ;
		}
		new_line = add_spaces(line, count_new_len(line, ft_strlen(line)));// add spaces before special symbols to split it after
		parse_line(new_line, &head, ft_strlen(new_line));
		if (syntax_error(head) == 1)
		{
			lstclear(&head);
			continue ;
		}
		expanding(&head);
		cmd_list = fill_cmds_list(&head);
		// (void)cmd_list;
		t_cmd *tmpp = cmd_list;
		while (tmpp)
		{
			i = 0;
			while(tmpp->cmd[i])
			{
				printf("COMMAND:  %s ----- INFILES: %s \n", tmpp->cmd[i], tmpp->files.infiles[i]);
				i++;
			}
			puts("____________________\n");
			tmpp = tmpp->next;
		}
		t_list *tmp  = head;
		while (tmp)
		{
			printf("%s =====>	%s\n", tmp->content, tmp->type == 1 ? "PIPE" : 
				tmp->type == 2 ? "HEREDOC" : tmp->type == 3 ? "APPEND" : tmp->type == 5 ? "IN" : 
					tmp->type == 6 ? "OUT" : tmp->type == 12 ? "DELEMETRE" : "WORD");
			tmp = tmp->next;
		}
		tmp = head;
		while (tmp)
		{
			printf("\n\nnode ------------------->%p\n\n", tmp->content);
			tmp = tmp->next;
		}
		printf("\n\n%p\n\n", line);
		printf("\n\n%p\n\n", new_line);
		free(line);
		free(new_line);
		lstclear(&head);
		clear_cmds_list(&cmd_list);
	}
}

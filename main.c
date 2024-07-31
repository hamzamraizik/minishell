#include "minishell.h"

char **ft_envp;
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
		/*syntax_error("quotes not closed");*/return (1);
	if (line && (line[0] == '|' || line[ft_strlen(line) - 1] == '|'))
		/*syntax_error("pipe in first or end");*/return (1);
	if (check_multi_pipes(line))
		/*syntax_error("multi pipes");*/return (1);
	if (in_out_check(line))
		return (1);
	return 0;
}

int	count_new_len(char *line, int old_len)
{
	int i;

	i = 0;
	while(line[i])
	{
		if(check_special(line[i]) && line[i + 1] != ' ')
				old_len += 2;
		i++;
	}
	return (old_len);
}

void	*parse_line(char *line, t_list	**head, int length)
{
	char **new_line;

	*head = NULL;
	line = add_delimetre(line);
	new_line = ft_new_split(line, '\0', length);
	tokenizing(head, new_line);
	// free_line(new_line);
	return (NULL);
}

int main(int argc, char **argv, char **envp)
{
	char	*line;
	char    *new_line;
	t_list	*head;

	(void)argc;
	(void)argv;
	// (void)envp;
	ft_envp = envp;
	head = NULL;
	while (1)
	{
		 line = readline(GREEN BOLD "Minishell " YELLOW BOLD"-> " RESET);
		add_history(line);
		if (check_if_empty(line) || first_syntax_check(line))
			continue ;
		new_line = add_spaces(line);
		parse_line(new_line, &head, ft_strlen(new_line));
		if (syntax_error(head) == 1 && !lstclear(head))
			continue ;
		expanding(&head);
		while(head != NULL)
		{
			printf("%s =====>	%s\n", head->content, head->type == 1 ? "PIPE" : head->type == 2 ? "HEREDOC" : head->type == 3 ? "APPEND" : head->type == 5 ? "IN" : head->type == 6 ? "OUT" : head->type == 8 ? "SEMI" : "WORD");
			head = head->next;
		}
		lstclear(head);
		// free(line);
		free(new_line);
		// split_env(envp);
	}
}

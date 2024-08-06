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
		return (printf("bash: syntax_error, quotes not closed\n"), 1);
	if (line && (line[0] == '|' || line[ft_strlen(line) - 1] == '|'))
		return (printf("bash: syntax error near unexpected token `|'\n"), 1);
	if (check_multi_pipes(line))
		return (printf("bash: syntax error near unexpected token `|'\n"), 1);
	if (in_out_check(line))
		return (printf("bash: syntax error\n"), 1);
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

void remove_quotes(t_list **head)
{
    t_list	*tmp;
    int		start, end, i, j;
    int		is_quotes = 0;
    char	*result;

    tmp = *head;
    while (tmp) {
        if (strchr(tmp->content, '"') || strchr(tmp->content, '\'')) {
            // Step 1: Find the first and last non-quote characters
            start = 0;
            end = strlen(tmp->content) - 1;

            // Skip leading outer quotes
            while (start <= end && (tmp->content[start] == '"' || tmp->content[start] == '\'')) {
                is_quotes = check_quotes(is_quotes, tmp->content[start]);
                if (is_quotes == 1 || is_quotes == 2) {
                    while (start <= end && tmp->content[start] != (is_quotes == 1 ? '\'' : '"')) {
                        start++;
                    }
                    if (start <= end) start++; // Skip the closing quote
                } else {
                    break;
                }
            }

            // Skip trailing outer quotes
            while (end >= start && (tmp->content[end] == '"' || tmp->content[end] == '\'')) {
                is_quotes = check_quotes(is_quotes, tmp->content[end]);
                if (is_quotes == 1 || is_quotes == 2) {
                    while (end >= start && tmp->content[end] != (is_quotes == 1 ? '\'' : '"')) {
                        end--;
                    }
                    if (end >= start) end--; // Skip the closing quote
                } else {
                    break;
                }
            }

            // Allocate memory for the result string
            result = malloc(end - start + 2); // +2 to include null terminator and possibly one character
            if (!result) {
                perror("malloc failed");
                exit(EXIT_FAILURE);
            }
            // Copy the content while preserving inner quotes
            i = start;
            j = 0;
            is_quotes = 0;
            while (i <= end) {
                is_quotes = check_quotes(is_quotes, tmp->content[i]);
                result[j++] = tmp->content[i++];
            }
            result[j] = '\0';

            // Update the list node with the new content
            free(tmp->content);
            tmp->content = result;
        }
        tmp = tmp->next;
    }
}

void	parse_line(char *line, t_list	**head, int length)
{
	char	**new_line;

	*head = NULL;
	line = add_delimetre(line);// replace space with '\0' for splite
	new_line = ft_new_split(line, '\0', length); // splite line with '\0'
	tokenizing(head, new_line); // listing it into tokenz
	// free_line(new_line);
	return ;
}

int main(int argc, char **argv, char **envp)
{
	char	*line;
	char    *new_line;
	t_list	*head;

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
		// remove_quotes(&head);
		while(head != NULL)
		{
			printf("%s =====>	%s\n", head->content, head->type == 1 ? "PIPE" : 
				head->type == 2 ? "HEREDOC" : head->type == 3 ? "APPEND" : head->type == 5 ? "IN" : 
					head->type == 6 ? "OUT" : head->type == 12 ? "DELEMETRE" : "WORD");
			head = head->next;
		}
		lstclear(head);
		// free(line);
		free(new_line);
		// split_env(envp);
	}
}

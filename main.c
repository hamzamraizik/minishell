#include "minishell.h"


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

char *add_spaces(char *line)
{
	int				new_len;
	char			*new_line;
	unsigned char	c;
	int				i;
	int				j;

	i = j = 0;
	new_len = count_new_len(line, ft_strlen(line));
	new_line = (char *)malloc(sizeof(char) * (new_len + 1));
	while (line[i])
	{
		if (line[i] && check_special(line[i]))
		{
			c = line[i];
			new_line[j] = ' ';
			while (line[i] == c)
				new_line[++j] = line[i++];
			new_line[++j] = ' ';
		}
		else
			new_line[j++] = line[i++];
	}
	new_line[j] = '\0';
	return (free(line), new_line);
}

char	*parse_line(char *line, int length)
{
	char **new_line;
	t_list	*head;

	head = NULL;
	length = ft_strlen(line);
	line = add_delimetre(line);
	new_line = ft_new_split(line, '\0', length);
	tokenizing(&head, new_line);
	while(head != NULL)
	{
		printf("%s %s\n", head->content, head->type == 1 ? "PIPE" : head->type == 2 ? "IN" : head->type == 3 ? "OUT" : head->type == 4 ? "SEMI" : "WORD");
		head = head->next;
	}
	// check_validity(head);
	return (line);
}

int main(int argc, char **argv, char **envp)
{
	char	*line;
	char    *line_2;
	int		line_length;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		line = readline(GRN"write a prompt: ");
		if (check_if_empty(line))
		{
			free(line);
			continue ;
		}
		// handle syntax error cases.
		add_history(line);
		line_2 = add_spaces(line);
		line_length = ft_strlen(line_2);
		line_2 = parse_line(line_2, line_length);
	}
}

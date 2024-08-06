#include "minishell.h"

/*this func loop over line and when fond space will replace it
	by '\0' and skip if there multiple spaces . i'm using 
		struct 'args' and func initial_init()
		   just for avoid norminette errors */
char	*add_spaces(char *line, int new_len)
{
	char			*new_line;
	unsigned char	c;
	t_args			args;

	initial_ints(&(args.i), &(args.j), &(args.is_quots));
	new_line = (char *)malloc(sizeof(char) * (new_len + 1));
	if (!new_line)
		return (NULL);
	while (line[args.i])
	{
		args.is_quots = check_quotes(args.is_quots, line[args.i]);
		if (line[args.i] && check_special(line[args.i]) && !args.is_quots)
		{
			c = line[args.i];
			new_line[args.j] = ' ';
			while (line[args.i] && line[args.i] == c)
				new_line[++args.j] = line[args.i++];
			new_line[++args.j] = ' ';
			++args.j;
		}
		else
			new_line[args.j++] = line[args.i++];
	}
	return (new_line[args.j] = '\0', free(line), new_line);
}

int	count_char(char *line, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	if (!line)
		return (0);
	while (line && line[i])
		if (line[i++] == c)
			++count;
	return (count);
}

char	*remove_char(char *line, char c)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = malloc(ft_strlen(line) - count_char(line, c) + 1);
	if (!str || !line)
		return (NULL);
	while (line && line[i])
	{
		if (line[i] == c)
			i++;
		else
			str[j++] = line[i++];
	}
	return (free(line), str);
}

int	syntax_error(t_list *head)
{
	t_list	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->next && tmp->type == HEREDOC && tmp->next->type != DELEMETRE)
			return (1);
		else if (tmp->next && tmp->type == APPEND && tmp->next->type != WORD)
			return (1);
		else if (tmp->next && tmp->type == IN && tmp->next->type != WORD)
			return (1);
		else if (tmp->next && tmp->type == OUT && tmp->next->type != WORD)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

#include "../includes/minishell.h"

int	isnum(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

void	initial_ints(int *i, int *j, int *k)
{
	if (i)
		*i = 0;
	if (j)
		*j = 0;
	if (k)
		*k = 0;
}

int check_if_empty(char *line)
{
	int i;

	i = 0;
	if (line[i] == '\0')
		return (1);
	while (line[i] == ' ')
		i++;
	if (!line[i])
		return (1);
	return (0);
}

int	check_special(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	else
		return (0);
}

int	check_quotes(int is_quotes, char c)
{
	if (is_quotes == 0 && c == '\'')
			is_quotes = 1;
	else if (is_quotes == 0 && c == '\"')
		is_quotes = 2;
	else if (is_quotes == 1 && c == '\'')
		is_quotes = 0;
	else if (is_quotes == 2 && c == '\"')
		is_quotes = 0;
	return (is_quotes);
}

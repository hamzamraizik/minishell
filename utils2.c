#include "minishell.h"

char *add_spaces(char *line)
{
	int				new_len;
	char			*new_line;
	unsigned char	c;
	int				i;
	int				j;
	int				is_quots;

	i = j = is_quots = 0;
	new_len = count_new_len(line, ft_strlen(line));
	new_line = (char *)malloc(sizeof(char) * (new_len + 1));
	while (line[i])
	{
		is_quots = check_quotes(is_quots, line[i]);
		if (line[i] && check_special(line[i]) && !is_quots)
		{
			c = line[i];
			new_line[j] = ' ';
			while (line[i] && line[i] == c)
				new_line[++j] = line[i++];
			new_line[++j] = ' ';
			++j;
		}
		else
			new_line[j++] = line[i++];
	}
	new_line[j] = '\0';
	return (free(line), new_line);
}

int count_char(char *line, char c)
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

char    *remove_char(char *line, char c)
{
	char	*str;
	int		i;
	int		j;

	i = j = 0;
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

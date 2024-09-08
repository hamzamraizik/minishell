#include "minishell.h"

static int	count_word(const char *s, char c, size_t len)
{
	int		count;
	int		c_fond;
	size_t	i;

	count  = 0;
	c_fond = 0;
	i = 0;
	while (i < len)
	{
		if (s[i] == c)
			c_fond = 0;
		else if (!c_fond && s[i] != c)
		{
			c_fond = 1;
			count++;
		}
		i++;
	}
	return (count);
}

static char	**free_substrs(char **substrs)
{
	int	i;

	i = 0;
	while (substrs[i])
		free(substrs[i++]);
	free(substrs);
	return (0);
}

static int	word_len(const char *s, char c, size_t len)
{
	int		count;
	size_t	i;

	i = 0;
	count = 0;
	while (i < len && s[i] != c)
	{
		count++;
		i++;
	}
	return (count);
}

char	**ft_new_split(const char *s, char c, size_t len)
{
	char	**substrs;
	int		i;
	int		word_length;
	size_t  j;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	substrs = (char **)malloc((count_word(s, c, len) + 1) * sizeof(char *));
	if (!substrs)
		return (NULL);
	while (j < len)
	{
		while (j < len && (s[j] == c || s[j] == ' ' || s[j] == '\t'))
			j++;
		if (j < len)
		{
			word_length = word_len(s + j, c, len - j);
			substrs[i] = ft_substr(s + j, 0, word_length);
			if (!substrs[i++])
				return (free_substrs(substrs));
			j += word_length;
		}
	}
	return (substrs[i] = NULL, substrs);
}

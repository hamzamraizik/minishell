#include <stdio.h>
#include <stdlib.h>
#include "libc.h"

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
size_t	ft_strlen( char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		count += 1;
		i++;
	}
	return (count);
}
char	*ft_substr(char  *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	if (start > (unsigned int)ft_strlen(s) || *s == '\0')
	{
		substr = malloc(1);
		if (!substr)
			return (NULL);
		substr[i] = '\0';
		return (substr);
	}
	// if (len > ft_strlen(s) - (size_t)start)
	// 	len = ft_strlen(s) - (size_t)start;
	substr = malloc(len + 1 * sizeof(char));
	if (!substr)
		return (NULL);
	i--;
	while (++i < len)
		substr[i] = s[start + i];
	substr[i] = '\0';
	return (substr);
}

// Updated count_word function to consider all delimiters
static int	count_word(char *s, char c, size_t len)
{
	int		count;
	int		c_fond;
	size_t	i;

	count  = 0;
	c_fond = 0;
	i = 0;
	while (i < len)
	{
		if (s[i] == c || s[i] == ' ' || s[i] == '\t')
			c_fond = 0;
		else if (!c_fond)
		{
			c_fond = 1;
			count++;
		}
		i++;
	}
	return (count);
}

// Updated word_len function
static int	word_len(char *s, char c, size_t len)
{
	int		count;
	size_t	i;

	i = 0;
	count = 0;
	while (i < len && s[i] != c && s[i] != ' ' && s[i] != '\t')
	{
		count++;
		i++;
	}
	return (count);
}

char	**ft_new_split(char *s, char c, size_t len)
{
	char	**substrs;
	int		i;
	int		word_length;
	size_t	j;

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
			substrs[i] = ft_substr(s + j, 0, word_length); // Ensure ft_substr is correct
			if (!substrs[i++])
				return (free_substrs(substrs));
			j += word_length;
		}
	}
	substrs[i] = NULL;
	return (substrs);
}


int main(int   argc, char **argv)
{
    int i = 0;
    char **new_line;
    char    *line = "kds'\0' |'\0'kfek |'\0'fek'\0'|'\0'   a'\0' |'\0' efkefk'\0' |'\0' hjj      |'\0'   fe'\0'   f'\0'|'\0'efdewfewfe'\0'|'\0'kjk'\0'|'\0'ls'\0'";
    
    printf("%s\n", line);
    new_line = ft_new_split(line, '\0', ft_strlen("kdsX |XkfekX |XfekX|X   aX |X efkefkX |X hjjX      |X   feX   fX|XefdewfewfeX|XkjkX|XlsX"));
    while (new_line[i])
    {
        printf("\nnew_line[%d]: %s\n", i, new_line[i]);
        i++;
    }
}

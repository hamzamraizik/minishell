#include "minishell.h"

char *var_expand(const char *word)
{
	char *result = strdup("");
	char *tmp;
	int i = 0, start = 0, is_quotes = 0;

	while (word[i])
	{
		if (word[i] == '"')
		{
			while (word[i] != '"')
			{
				if (word[i] == '$')
				{
					tmp = strndup(word + start, i - start);
					result = ft_strjoin(result, tmp);
					free(tmp);
					++i;
					while (word[i] != ' ' && word[i] != '$' && word[i] != '"')
					{
						
					}
				}
				i++;
			}
		}
		i++;
	}
}
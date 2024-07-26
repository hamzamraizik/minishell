# include "minishell.h"

void s_with_d_Q(char *s)
{
	int i;
	int is_quotes;

	i = is_quotes = 0;
	while (s[i])
	{
		is_quotes = check_quotes(is_quotes, s[i]);
		if (!is_quotes && s[i + 1] == '"')
		{
			if (s[i+2] == '$')
			{
				write(1, "hnaa\n", 5);
				exit(1);
			}
			i++;
		}
		else
				i++;
	}
}

#include "../minishell.h"

char	*is_var(char **env, char *var)
{
	int		i;
	// int		j;
	char	**line;
	char	*result;

	i = 0;
	// j = 0;
	result = strdup("");
	while (env[i])
	{
		line = ft_split(env[i], '=');
		if (strcmp(line[0], var) == 0)
		{
			var = line[1];
			result = strdup(var);
			return result;
		}
		i++;
	}
	return(result);
}
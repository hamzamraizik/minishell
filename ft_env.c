#include "minishell.h"

char	*is_var(char **env, char *var)
{
	int		i;
	// int		j;
	char	**line;
	char	*result;

	i = 0;
	// j = 0;
	result = NULL;
	while (env[i])
	{
		line = ft_split(env[i], '=');
		if (strcmp(line[0], var) == 0)
		{
			var = line[1];
			result = strdup(var);
			free(line[0]);
			free(line[1]);
			free(line);
			return (result);
		}
		i++;
	}
	return ((result = strdup("")));
}
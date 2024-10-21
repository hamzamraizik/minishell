/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commande_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochangli <ochangli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:42:55 by ochangli          #+#    #+#             */
/*   Updated: 2024/10/18 16:23:18 by ochangli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

/*This function return the full path of a commande*/
char	*get_cmd_exec(char *cmd, char **env)
{
	char	*path_line;

	path_line = get_path_exec("PATH=", env);
	if (!path_line)
		return (no_path(cmd));
	else
		return (with_path(cmd, path_line));
	return (cmd);
}

/*The function return a pointer to the path string in envirement*/
char	*get_path_exec(const char *s, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strcmp_2(s, envp[i]) == 0)
			return (envp[i]);
		i++;
	}
	return (NULL);
}

/*The full path function return the commande with it's
a path from the  envirement */
char	*get_full_path_exec(char *cmd, char *path_env)
{
	int		total_len;
	char	*path;

	total_len = ft_strlen_exec(path_env) + ft_strlen_exec(cmd);
	path = ft_concatinate_exec(cmd, path_env, total_len);
	if (!path)
		return (NULL);
	return (path);
}

/*the function loop throught all the envirement and 
each time check the valid path for the commande*/
char	*get_final_path_exec(char *cmd, char **envp)
{
	int			i;
	char		*full_path;
	const char	*tmp;	

	i = 0;
	if (!cmd[0])
		return (NULL);
	while (envp[i])
	{
		full_path = get_full_path_exec(cmd, envp[i]);
		if (!full_path)
			return (NULL);
		tmp = full_path;
		if (access(tmp, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

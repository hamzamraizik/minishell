/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochangli <ochangli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 14:03:42 by ochangli          #+#    #+#             */
/*   Updated: 2024/10/18 16:24:06 by ochangli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char	*no_path(char	*commande)
{
	if (!is_directory(commande))
		return (is_directory_error(commande), NULL);
	if (access(commande, F_OK | X_OK) == 0)
		return (commande);
	if (access(commande, F_OK) == 0)
	{
		if (is_directory(commande) == 2 && access(commande, X_OK))
			return (permission_denied(commande), NULL);
	}
	return (commande);
}

char	*with_path(char	*cmd, char	*path_line)
{
	char	*cmd_final;
	char	**paths;

	paths = ft_split_exec(path_line + 5, ':');
	if (!paths)
	{
		freing_exec(paths);
		no_file_or_dir(cmd);
	}
	if (ft_strchr(cmd, '/'))
	{
		if (!is_directory(cmd))
			return (is_directory_error(cmd), NULL);
		else if (access(cmd, F_OK | X_OK) == 0)
			return (freing_exec(paths), cmd);
		else
			no_file_or_dir_exec(cmd);
	}
	cmd_final = get_final_path_exec(cmd, paths);
	if (cmd_final)
		return (cmd_final);
	if (!cmd_final && !ft_strchr(cmd, '/'))
		commande_not_found_exec(cmd);
	return (freing_exec(paths), cmd_final);
}

/*This function commpare two strings */
int	ft_strcmp_2(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (-1);
		i++;
	}
	return (0);
}

/*This function simply return The len of a string*/
int	ft_strlen_exec(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

/*This function is used to creat and allocate memory for a node*/
t_my_env	*ft_lstnew_exec(char *variable, char	*data)
{
	t_my_env	*new_node;

	new_node = malloc(sizeof(t_my_env));
	if (!new_node)
		return (NULL);
	new_node->variable = variable;
	new_node->data = data;
	new_node->next = NULL;
	return (new_node);
}

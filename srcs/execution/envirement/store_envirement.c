/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_envirement.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochangli <ochangli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 10:15:44 by ochangli          #+#    #+#             */
/*   Updated: 2024/10/18 00:44:02 by ochangli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

/*This function is used to return the len of the 
 * Varibale before the '='*/
size_t	var_len_exec(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '=')
		i++;
	return (i);
}

/*This function is used to allocate and return the name of
*a variable in the envirement*/
char	*get_variable_exec(char *string)
{
	int		i;
	size_t	len;
	char	*my_variable;

	i = 0;
	len = var_len_exec(string) + 1;
	my_variable = malloc(len);
	if (!my_variable)
		return (NULL);
	while (string[i] != '=')
	{
		my_variable[i] = string[i];
		i++;
	}
	my_variable[i] = '\0';
	return (my_variable);
}

/*This function is used to allocate and return the value of
*a variable in the envirement*/
char	*get_data_exec(char *string)
{
	int		i;
	int		j;
	size_t	len;
	char	*my_data;

	i = 0;
	j = 0;
	len = data_len_exec(string) + 1;
	my_data = malloc(len);
	if (!my_data)
		return (NULL);
	while (string[i] != '=')
		i++;
	i++;
	while (string[i] != '\0')
	{
		my_data[j] = string[i];
		i++;
		j++;
	}
	my_data[j] = '\0';
	return (my_data);
}

/*This fumction is used to store the envirememt in a linked list , 
 *each line in an array of chars , with variable , and data*/
void	get_bash_env_exec(t_my_env	**head, char	**env)
{
	int			i;
	char		*variable;
	char		*data;
	t_my_env	*node;

	i = 0;
	while (env[i])
	{
		variable = get_variable_exec(env[i]);
		data = get_data_exec(env[i]);
		node = ft_lstnew_exec(variable, data);
		ft_lstadd_back_exec(head, node);
		i++;
	}
}

/*the fnuctionconcatinate two strings , the user provided commande 
and the path */
char	*ft_concatinate_exec(const char *s1, const char *s2, int len)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	new = malloc(len + 2);
	if (!new)
		return (NULL);
	while (s2[i])
		new[j++] = s2[i++];
	new[j] = 47;
	j++;
	i = 0;
	while (s1[i])
		new[j++] = s1[i++];
	new[j] = '\0';
	return (new);
}

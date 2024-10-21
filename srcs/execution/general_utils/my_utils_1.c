/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochangli <ochangli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 13:59:09 by ochangli          #+#    #+#             */
/*   Updated: 2024/10/14 12:57:01 by ochangli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

/*This function used to transer and strng to lower format*/
char	*to_lower_exec(char *cmd)
{
	int		i;
	char	*new_lower;

	i = 0;
	new_lower = malloc(ft_strlen_exec(cmd) + 1);
	while (cmd[i] != '\0')
	{
		if (cmd[i] >= 'A' && cmd[i] <= 'Z')
			new_lower[i] = cmd[i] + 32;
		else
			new_lower[i] = cmd[i];
		i++;
	}
	return (new_lower);
}

/*This function is used to add a node into The end of a linked list*/
void	ft_lstadd_back_exec(t_my_env **lst, t_my_env *new)
{
	t_my_env	*temp;

	if (!new || !lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}

/*This function return the size of a 2D array*/
int	array_lenght(char **array)
{
	int	i;

	if (!array)
		return (0);
	i = 0;
	while (array[i])
		i++;
	return (i);
}

/*This function is used to calculate the len after the '=' sign */
size_t	data_len_exec(char *s)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (s[i] != '=')
		i++;
	i++;
	while (s[i])
	{
		i++;
		j++;
	}
	return (j);
}

/*This function copies a string into another one*/
void	ft_strcpy_exec(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i] != '\0')
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return ;
}

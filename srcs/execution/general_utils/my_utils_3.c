/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_utils_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochangli <ochangli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 14:56:52 by ochangli          #+#    #+#             */
/*   Updated: 2024/10/18 17:53:18 by ochangli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

/*This function free a duble pointer array*/
void	freing_exec(char **p)
{
	int	i;

	i = 0;
	if (!p)
		return ;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free (p);
}

/*This function made to search is ther is a special character in the string s*/
int	ft_strchr_exec(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == c)
			return (0);
		i++;
	}
	return (-1);
}

int	ft_strcmp_exec(const char *s1, const char *s2, int type)
{
	if (!s1)
		return (1);
	if (type)
	{
		while (*s1 != '\0' || *s2 != '\0')
		{
			if (*s1 != *s2 && (*s1 != (*s2 - 32)))
				return ((unsigned char)*s1 - (unsigned char)*s2);
			s1++;
			s2++;
		}
	}
	else
	{
		while (*s1 != '\0' || *s2 != '\0')
		{
			if (*s1 != *s2)
				return ((unsigned char)*s1 - (unsigned char)*s2);
			s1++;
			s2++;
		}
	}
	return (0);
}

void	free_int_array(void	**array, int size)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

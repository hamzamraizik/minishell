/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochangli <ochangli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 07:05:14 by ochangli          #+#    #+#             */
/*   Updated: 2024/10/17 14:59:24 by ochangli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

/*This commnade commpare Two strings */
int	ft_strmycmp(char *s1, char	*s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

/*This function return The index of a file in the array*/
int	get_file_index(char *file_name, char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (ft_strmycmp(file_name, array[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

/*This function check if a file exist in an array of files */
int	is_exist_in_array(char **files, char *file_name)
{
	int	i;

	i = 0;
	while (files[i])
	{
		if (!ft_strmycmp(files[i], file_name))
			return (1);
		i++;
	}
	return (0);
}

int	is_ambiguous(char *s, t_files allfiles, int index)
{
	int	i;

	i = 0;
	if (s[0] == '\0' || is_contain_spaces(s))
	{
		while (allfiles.ambiguous_indexes[i] != -1)
		{
			if (index == allfiles.ambiguous_indexes[i])
				return (0);
			i++;
		}
	}
	return (1);
}

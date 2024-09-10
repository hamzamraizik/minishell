/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizoo <mizoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 13:44:52 by hmraizik          #+#    #+#             */
/*   Updated: 2024/09/10 01:03:33 by mizoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	count_word( char *s, char c)
{
	int	count;
	int	c_fond;

	count = 0;
	c_fond = 0;
	while (*s)
	{
		if (*s == c)
			c_fond = 0;
		else if (!c_fond && *s != c)
		{
			c_fond = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static char	**free_substrs(char **substrs)
{
	int	i;

	i = 0;
	while (substrs[i])
		free(substrs[i++]);
	free(substrs);
	return (0);
}

static int	word_len(char  *s, char c)
{
	int	count;

	count = 0;
	while (*s && *(s++) != c)
		count++;
	return (count);
}

char	**ft_split(char  *s, char c)
{
	char	**substrs;
	int		i;
	int		len;

	if (!s)
		return (0);
	substrs = (char **)malloc((count_word(s, c) + 1) * sizeof(char *));
	if (!substrs)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && (*s == c || *s == ' '))
			s++;
		if (*s)
		{
			len = word_len(s, c);
			substrs[i] = ft_substr(s, 0, len);
			if (!substrs[i++])
				return (free_substrs(substrs));
			s += len;
		}
	}
	substrs[i] = 0;
	return (substrs);
}

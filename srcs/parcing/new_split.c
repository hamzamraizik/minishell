/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmraizik <hmraizik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 23:30:19 by hmraizik          #+#    #+#             */
/*   Updated: 2024/10/16 23:30:20 by hmraizik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_word(const char *s, char c, size_t len)
{
	int		count;
	int		c_fond;
	size_t	i;

	count = 0;
	c_fond = 0;
	i = 0;
	while (i < len)
	{
		if (s[i] == c)
			c_fond = 0;
		else if (!c_fond && s[i] != c)
		{
			c_fond = 1;
			count++;
		}
		i++;
	}
	return (count);
}

static int	word_len(const char *s, char c, size_t len)
{
	int		count;
	size_t	i;

	i = 0;
	count = 0;
	while (i < len && s[i] != c)
	{
		count++;
		i++;
	}
	return (count);
}

char	**ft_new_split(char *s, char c, int len)
{
	char	**substrs;
	int		i;
	int		word_length;
	int		j;

	if (!s)
		return (NULL);
	initial_ints(&i, &j, NULL);
	substrs = (char **)malloc((count_word(s, c, len) + 1) * sizeof(char *));
	if (!substrs)
		return (NULL);
	while (j < len)
	{
		while (j < len && (s[j] == c || s[j] == ' ' || s[j] == '\t'))
			j++;
		if (j < len)
		{
			word_length = word_len(s + j, c, len - j);
			substrs[i] = ft_substr(s + j, 0, word_length);
			if (!substrs[i++])
				return (free_substrs(substrs));
			j += word_length;
		}
	}
	return (substrs[i] = NULL, substrs);
}

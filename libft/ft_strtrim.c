/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizoo <mizoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 00:46:07 by hmraizik          #+#    #+#             */
/*   Updated: 2024/09/10 21:42:30 by mizoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_kayna(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	int	start;
	int	end;

	if (!s1 || !set)
		return (NULL);
	if (*s1 == 0)
		return (ft_strdup(""));
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && ft_kayna(s1[start], set))
		start++;
	while (s1[end] && ft_kayna(s1[end], set))
		end--;
	if (end == -1)
		return (ft_substr(s1, start, 0));
	return (ft_substr(s1, start, (end - start + 1)));
}

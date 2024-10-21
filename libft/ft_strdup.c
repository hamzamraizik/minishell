/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmraizik <hmraizik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:04:48 by hmraizik          #+#    #+#             */
/*   Updated: 2024/10/14 06:39:44 by hmraizik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *s1)
{
	size_t	len;
	char	*s2;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1) + 1;
	s2 = malloc(len * sizeof(char));
	if (s1 == NULL)
		return (NULL);
	if (s2 != NULL)
	{
		ft_memcpy(s2, s1, len - 1);
		s2[len - 1] = '\0';
	}
	return (s2);
}

char	*ft_strndup(char *s1, int n)
{
	char	*s2;
	int		i;

	i = 0;
	s2 = malloc(n + 1 * sizeof(char));
	if (!s2)
		return (NULL);
	while (s1 && s1[i] && i < n)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

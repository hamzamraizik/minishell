/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizoo <mizoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:40:12 by hmraizik          #+#    #+#             */
/*   Updated: 2024/09/10 15:34:26 by mizoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char  *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	if (start > (unsigned int)ft_strlen(s) || *s == '\0')
	{
		substr = malloc(1);
		if (!substr)
			return (NULL);
		substr[i] = '\0';
		return (substr);
	}
	// if (len > ft_strlen(s) - (size_t)start)
	// 	len = ft_strlen(s) - (size_t)start;
	substr = malloc(len + 1 * sizeof(char));
	if (!substr)
		return (NULL);
	i--;
	// while (++i < len && s[start + i])
	// 	substr[i] = s[start + i];
	// substr[i] = '\0';
	ft_strlcpy(substr, s + start, len + 1);
	return (substr);
}

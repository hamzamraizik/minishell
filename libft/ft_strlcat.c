/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizoo <mizoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:55:07 by hmraizik          #+#    #+#             */
/*   Updated: 2024/09/10 21:41:09 by mizoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t		len1;
	size_t		len2;
	size_t		i;

	if (!dst && size == 0)
		return (ft_strlen(src));
	len1 = ft_strlen(dst);
	len2 = ft_strlen(src);
	i = 0;
	if (len1 >= size)
		return (len2 + size);
	if (size == 0)
		return (len2);
	i = 0;
	if (size <= len1)
		return (len2 + size);
	while ((len1 + i) < (size - 1) && src[i])
	{
		dst[len1 + i] = src[i];
		i++;
	}
	dst[len1 + i] = '\0';
	return (len1 + len2);
}

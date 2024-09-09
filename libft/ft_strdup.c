/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmraizik <hmraizik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:04:48 by hmraizik          #+#    #+#             */
/*   Updated: 2024/08/26 01:50:56 by hmraizik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *s1)
{
	size_t	len;
	char	*s2;

	len = ft_strlen(s1) + 1;
	s2 = malloc(len);
	if (s1 == NULL)
		return (NULL);
	if (s2 != NULL)
	{
		ft_memcpy(s2, s1, len - 1);
		s2[len - 1] = '\0';
	}
	return (s2);
}

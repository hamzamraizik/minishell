/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizoo <mizoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:04:48 by hmraizik          #+#    #+#             */
/*   Updated: 2024/08/09 17:53:30 by mizoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *s1, int n)
{
	size_t	len;
	char	*s2;

	len = n + 1;
	s2 = malloc(len);
	if (!s1)
		return (NULL);
	if (s2 != NULL)
	{
		ft_memcpy(s2, s1, len - 1);
		s2[len - 1] = '\0';
	}
	return (s2);
}

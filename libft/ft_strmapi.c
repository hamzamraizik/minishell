/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizoo <mizoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:31:22 by hmraizik          #+#    #+#             */
/*   Updated: 2024/09/10 21:43:28 by mizoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len;
	char	*new;

	if (!s || !f)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	new = (char *)malloc(len * (sizeof(char)) + 1);
	if (new)
	{
		while (i < len)
		{
			new[i] = f(i, s[i]);
			i++;
		}
		new[i] = '\0';
	}
	return (new);
}
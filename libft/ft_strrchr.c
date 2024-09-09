/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmraizik <hmraizik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:36:52 by hmraizik          #+#    #+#             */
/*   Updated: 2024/08/26 01:47:56 by hmraizik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr( char *s, int c)
{
	int	len;

	len = ft_strlen(s);
	if (*(s + len) == 0 && (char)c == 0)
		return ((char *)(s + len));
	len--;
	while (len >= 0)
	{
		if ((char)c == s[len])
			return ((char *)&s[len]);
		len--;
	}
	return (NULL);
}

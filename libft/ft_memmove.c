/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizoo <mizoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:20:00 by hmraizik          #+#    #+#             */
/*   Updated: 2024/09/10 21:41:28 by mizoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, void *src, size_t n)
{
	char	*d;
	char	*s;

	d = (char *) dest;
	s = (char *)src;
	if (d == s || n == 0)
		return (dest);
	if (d < s)
		ft_memcpy(dest, src, n);
	else
	{
		d += n - 1;
		s += n - 1;
		while (n--)
		{
			*d = *s;
			d--;
			s--;
		}
	}
	return (dest);
}

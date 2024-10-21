/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmraizik <hmraizik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:14:41 by hmraizik          #+#    #+#             */
/*   Updated: 2023/12/03 02:02:46 by hmraizik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n_elements, size_t s_elements)
{
	void			*p;
	size_t			c;

	c = n_elements * s_elements;
	if (s_elements != 0 && c / s_elements != n_elements)
		return (NULL);
	p = malloc(n_elements * s_elements);
	if (!p)
		return (NULL);
	ft_bzero(p, n_elements * s_elements);
	return (p);
}

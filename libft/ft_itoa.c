/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmraizik <hmraizik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 13:47:39 by hmraizik          #+#    #+#             */
/*   Updated: 2023/12/24 18:15:39 by hmraizik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_digits(int n)
{
	size_t	i;

	i = !n;
	if (n < 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*str;
	size_t		count;
	long int	number;

	number = n;
	count = count_digits(n);
	str = (char *)malloc(sizeof(char) * (count + 1));
	if (!str)
		return (NULL);
	if (n < 0)
		number *= -1;
	str[count] = 0;
	while (count--)
	{
		str[count] = number % 10 + '0';
		number /= 10;
	}
	if (n < 0)
		*str = '-';
	return (str);
}

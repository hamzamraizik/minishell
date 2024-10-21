/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmraizik <hmraizik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:30:18 by hmraizik          #+#    #+#             */
/*   Updated: 2024/10/16 23:24:18 by hmraizik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*this fuction check if the content that will be expanded if there 
 is pipes before it, wich means there isn't in the first command
 	this needed in the expansion of exit status
*/
int	pipe_before(t_list *tmp)
{
	t_list	*tmp2;

	tmp2 = tmp;
	while (tmp2)
	{
		if (tmp2->type == PIPE)
			return (1);
		tmp2 = tmp2->prev;
	}
	return (0);
}

int	is_empty(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

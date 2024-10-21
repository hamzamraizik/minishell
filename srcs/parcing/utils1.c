/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochangli <ochangli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 23:29:37 by hmraizik          #+#    #+#             */
/*   Updated: 2024/10/18 03:54:43 by ochangli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initial_ints(int *i, int *j, int *k)
{
	if (i)
		*i = 0;
	if (j)
		*j = 0;
	if (k)
		*k = 0;
}

int	check_if_empty(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '\0')
		return (free(line), 1);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (!line[i])
		return (free(line), 1);
	return (0);
}

int	check_special(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	else
		return (0);
}

int	check_quotes(int is_quotes, char c)
{
	if (is_quotes == 0 && c == '\'')
		is_quotes = 1;
	else if (is_quotes == 0 && c == '\"')
		is_quotes = 2;
	else if (is_quotes == 1 && c == '\'')
		is_quotes = 0;
	else if (is_quotes == 2 && c == '\"')
		is_quotes = 0;
	return (is_quotes);
}

int	is_contain_spaces(char *line)
{
	if (ft_strchr(line, ' ') || ft_strchr(line, '\t'))
		return (1);
	return (0);
}

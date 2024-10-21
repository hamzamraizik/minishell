/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmraizik <hmraizik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:49:29 by hmraizik          #+#    #+#             */
/*   Updated: 2024/10/12 15:06:33 by hmraizik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_multi_pipes(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if ((line[i] == '|' && line[i + 1] == '|' && line[i + 2] == '|')
			|| (line[i] == '|' && line[i + 1] == ' ' && line[i + 2] == '|'))
			return (1);
		i++;
	}
	return (0);
}

int	in_out_check(char *line)
{
	int	i;
	int	j;

	initial_ints(&i, &j, NULL);
	while (line[i])
	{
		if ((line[i] == '<' && line[i + 1] != '<' && check_special(line[i + 1])
				&& printf("Minishell: Syntax Error!\n"))
			|| (line[i] == '<' && (line[i + 1] == '<' || line[i + 1] == ' ')
				&& line[i + 2] == '<' && printf("Minishell: Syntax Error!\n")))
			return (1);
		if ((line[i] == '>' && line[i + 1] != '>' && check_special(line[i + 1])
				&& printf("Minishell: Syntax Error!\n"))
			|| (line[i] == '>' && (line[i + 1] == '>' || line[i + 1] == ' ')
				&& line[i + 2] == '>' && printf("Minishell: Syntax Error!\n")))
			return (1);
		if (in_out_check2(line, &i, &j) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	first_syntax_check(char *line)
{
	int	is_quotes;
	int	i;

	initial_ints(&is_quotes, &i, NULL);
	while (line[i])
		is_quotes = check_quotes(is_quotes, line[i++]);
	if (is_quotes != 0)
		return (
			printf("Minishell: syntax_error, "
				"quotes not closed\n"), 1);
	while (*line == ' ' || *line == '\t')
		line++;
	if (line && line[0] == '|')
		return (
			printf("Minishell: Syntax Error!\n"), 1);
	if (line && check_special(line[ft_strlen(line) - 1])
		&& line[ft_strlen(line) - 1] != '>')
		return (
			printf("Minishell: Syntax Error!\n"), 1);
	if (check_multi_pipes(line))
		return (
			printf("Minishell: Syntax Error!\n"), 1);
	if (in_out_check(line))
		return (1);
	return (0);
}

int	count_new_len(char *line, int old_len)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (check_special(line[i]))
			old_len += 2;
		i++;
	}
	return (old_len);
}

char	**free_substrs(char **substrs)
{
	int	i;

	i = 0;
	while (substrs && substrs[i])
	{
		free(substrs[i++]);
		substrs[i - 1] = NULL;
	}
	if (substrs)
		free(substrs);
	return (NULL);
}

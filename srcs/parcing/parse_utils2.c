/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochangli <ochangli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:02:25 by hmraizik          #+#    #+#             */
/*   Updated: 2024/10/18 01:05:51 by ochangli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_out_check2(char *line, int *i, int *j)
{
	if (check_special(line[(*i)]) && line[(*i) + 1] == '\0'
		&& printf("mini_hell: Syntax Error!\n"))
		return (1);
	if (line[(*i)] == '<' || line[(*i)] == '>')
	{
		(*j) = (*i) + 1;
		while (line[(*j)] && ft_isdigit(line[(*j)]))
			(*j)++;
		if (((*j) - (*i)) > 1 && (line[(*j)] == '<' || line[(*j)] == '>')
			&& printf("mini_hell: Syntax Error!\n"))
			return (1);
	}
	return (0);
}

int	free_things(void *ptr, void *ptr1, t_list *ptr2)
{
	if (ptr)
		free(ptr);
	if (ptr1)
		free(ptr1);
	(void)ptr2;
	if (ptr2)
		lstclear(&ptr2);
	ptr = NULL;
	ptr1 = NULL;
	ptr2 = NULL;
	return (1);
}

void	refresh_stat(char *new_line, char *line, t_list *head, t_termios *term)
{
	free_things(new_line, line, head);
	tcsetattr(0, TCSANOW, term);
	g_signal = 0;
}

int	add_line_to_history(char *line, t_infos *infos)
{
	if (check_if_empty(line))
	{
		if (line && line[0])
			add_history(line);
		return (1);
	}
	add_history(line);
	if (first_syntax_check(line))
	{
		(free(line), line = NULL, infos->exit_status = 258);
		return (1);
	}
	return (0);
}

void	sig_int_status(t_infos *infos)
{
	if (g_signal == 2)
	{
		infos->exit_status = 1;
		g_signal = 0;
	}
}

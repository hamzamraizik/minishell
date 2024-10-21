/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochangli <ochangli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 23:29:24 by hmraizik          #+#    #+#             */
/*   Updated: 2024/10/18 16:21:17 by ochangli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*this func loop over line and when fond space will replace it
	by '\0' and skip if there multiple spaces . i'm using 
		struct 'args' and func initial_init()
		   just for avoid norminette errors */
char	*add_spaces(char *line, int new_len)
{
	char			*new_line;
	unsigned char	c;
	t_args			args;

	initial_ints(&(args.i), &(args.j), &(args.is_quots));
	new_line = malloc(sizeof(char) * ((new_len) + 1));
	if (!new_line)
		return (ft_putstr_fd("malloc failed!\n", 2), NULL);
	while (line && line[args.i])
	{
		args.is_quots = check_quotes(args.is_quots, line[args.i]);
		if (line[args.i] && check_special(line[args.i]) && !args.is_quots)
		{
			c = line[args.i];
			new_line[args.j] = ' ';
			while (line[args.i] && line[args.i] == c)
				new_line[++args.j] = line[args.i++];
			if (line[args.i])
				new_line[++args.j] = ' ';
			++args.j;
		}
		else
			new_line[args.j++] = line[args.i++];
	}
	return (new_line[args.j] = '\0', new_line);
}

int	syntax_error(t_list *head)
{
	t_list	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->next && tmp->type == HEREDOC && tmp->next->type != DELEMETRE)
			return (
				printf("minishell: Syntax Error! near "
					"unexpected token `%s'\n", tmp->next->content), 1);
		else if (tmp->next && tmp->type == APPEND && tmp->next->type != WORD)
			return (printf("minishell: Syntax Error! near "
					"unexpected token `%s'\n", tmp->next->content), 1);
		else if (tmp->next && tmp->type == IN && tmp->next->type != WORD)
			return (printf("minishell: Syntax Error! near "
					"unexpected token `%s'\n", tmp->next->content), 1);
		else if (tmp->next && tmp->type == OUT && tmp->next->type != WORD)
			return (printf("minishell: Syntax Error! near "
					"unexpected token `%s'\n", tmp->next->content), 1);
		tmp = tmp->next;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmraizik <hmraizik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 23:30:03 by hmraizik          #+#    #+#             */
/*   Updated: 2024/10/16 23:30:04 by hmraizik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenizing(t_list **head, char **line)
{
	int	i;
	int	flag;

	initial_ints(&i, &flag, NULL);
	while (line && line[i])
	{
		if (ft_strncmp(line[i], "|", 1) == 0)
			flag = list_add_back(head, creat_node(line[i], PIPE));
		else if (ft_strncmp(line[i], "<<", 2) == 0)
			flag = list_add_back(head, creat_node(line[i], HEREDOC));
		else if (ft_strncmp(line[i], "<", 1) == 0)
			flag = list_add_back(head, creat_node(line[i], IN));
		else if (ft_strncmp(line[i], ">>", 2) == 0)
			flag = list_add_back(head, creat_node(line[i], APPEND));
		else if (ft_strncmp(line[i], ">", 1) == 0)
			flag = list_add_back(head, creat_node(line[i], OUT));
		else if (get_last_node(*head) && get_last_node(*head)->type == HEREDOC)
			flag = list_add_back(head, creat_node(line[i], DELEMETRE));
		else
			flag = list_add_back(head, creat_node(line[i], WORD));
		if (flag == 1)
			return (1);
		i++;
	}
	return (free(line), 0);
}

char	*add_delimetre(char *line, int length)
{
	int		i;
	int		is_quotes;

	i = 0;
	is_quotes = 0;
	while (i < length)
	{
		is_quotes = check_quotes(is_quotes, line[i]);
		if (is_quotes == 0 && (line[i] == ' ' || line[i] == '\t'))
		{
			line[i] = '\0';
			while (line[i + 1] == ' ' || line[i + 1] == '\t')
				i++;
		}
		i++;
	}
	line[i] = '\0';
	return (line);
}

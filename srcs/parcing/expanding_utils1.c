/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmraizik <hmraizik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:48:56 by hmraizik          #+#    #+#             */
/*   Updated: 2024/10/17 07:15:51 by hmraizik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* this func take the characters that exist before expand the actual variable
 			and join it to the result like : "hello$USER" -> it will join 
					the word hello before expand $USER.
*/
void	take_previous(char **result, char *word, int start, int i)
{
	char	*tmp;

	if (!word)
		return ;
	tmp = ft_strndup(word + start, i - start);
	*result = ft_strjoin(*result, tmp);
	free(tmp);
}

/* this function just remove the spaces that
	exist after expanding the variable
		from the env if it contains
			multiple spaces. */
char	*remove_var_spaces(char *tmp)
{
	char	**splited;
	char	*result;
	int		i;

	i = 0;
	if (!tmp)
		return (NULL);
	splited = ft_split(tmp, ' ');
	if (!splited)
		return (NULL);
	result = ft_strdup("");
	if (tmp[0] == ' ' || tmp[0] == '\t')
		result = ft_strjoin(result, " ");
	while (splited && splited[i])
	{
		result = ft_strjoin(result, splited[i]);
		if (splited[i + 1] || tmp[ft_strlen(tmp) - 1] == ' '
			|| tmp[ft_strlen(tmp) - 1] == ' ')
			result = ft_strjoin(result, " ");
		i++;
	}
	free_substrs(splited);
	if (tmp)
		free(tmp);
	return (result);
}

/* just some conditions to check the accepted
	characters after the dollar sign
*/
int	accepted_chars(t_list *tmp)
{
	if (*(ft_strchr(tmp->content, '$') + 1) == '$'
		|| *(ft_strchr(tmp->content, '$') + 1) == '_'
		|| *(ft_strchr(tmp->content, '$') + 1) == '?'
		|| *(ft_strchr(tmp->content, '$') + 1) == '-'
		|| *(ft_strchr(tmp->content, '$') + 1) == '"'
		|| *(ft_strchr(tmp->content, '$') + 1) == '\'')
		return (1);
	else
		return (0);
}

int	special_vars(char **result, char **str, int *start, int *index)
{
	int	flag;

	flag = 0;
	if ((*str)[*index] == '$' && (*str)[*index + 1] == '0')
	{
		flag = 1;
		take_previous(result, *str, *start, *index);
		*result = ft_strjoin(*result, "bash");
		(*start) = (++(*index)) + 1;
	}
	else if ((*str)[*index] == '$' && (*str)[*index + 1] == '-')
	{
		flag = 1;
		take_previous(result, *str, *start, *index);
		*result = ft_strjoin(*result, "himBH");
		(*start) = (++(*index)) + 1;
	}
	else if ((*str)[*index] == '$' && (*str)[*index + 1]
		&& ft_isdigit((*str)[*index + 1]))
	{
		flag = 2;
		take_previous(result, *str, *start, *index);
		(*start) = (++(*index)) + 1;
	}
	return (flag);
}

void	d_q_var_part2(char **result, char *str, int *start, int *index)
{
	if (str[*index] == '$' && str[*index + 1] == '$')
	{
		(*index) += 2;
		take_previous(result, str, *start, (*index));
		*start = (*index);
	}
	else
		(*index)++;
}

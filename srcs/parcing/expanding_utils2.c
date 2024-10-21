/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmraizik <hmraizik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:49:00 by hmraizik          #+#    #+#             */
/*   Updated: 2024/10/14 06:09:48 by hmraizik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*this func for the case when there is $$VAR
	will join each two '$' and expand
		just if there an single '$' */
int	double_dollar_cases(char **result, char *word, int tab[])
{
	int		flag;

	flag = 0;
	if (word[(tab[0])] == '$' && (word[(tab[0]) + 1] == '$'
			|| word[(tab[0]) + 1] == '"' || word[(tab[0]) + 1] == '\''))
	{
		if (word[(tab[0]) + 1] == '$')
		{
			(tab[0]) += 2;
			take_previous(result, word, (tab[1]), (tab[0]));
		}
		else
		{
			take_previous(result, word, (tab[1]), (tab[0]));
			++(tab[0]);
		}
		(tab[1]) = tab[0];
		flag = 1;
	}
	return (flag);
}

/* this function handle the symbol '~' 
    and expand it to the home path
*/
char	*handle_home_symbol(char *str, t_infos *infos)
{
	char	*result;
	int		i;
	int		start;

	i = 0;
	start = 0;
	if (str && str[i] && str[i] == '~' && str[i + 1] == '/')
	{
		result = my_getenv_var("HOME", infos);
		result = ft_strjoin(result, "/");
		start += 2;
		while (str[i])
			i++;
		take_previous(&result, str, start, i);
	}
	else if (str && str[i] && str[0] == '~' && str[i + 1] == '\0')
		result = my_getenv_var("HOME", infos);
	else
		return (ft_strdup(str));
	return (result);
}

/*this func will handle the double quotes when there is an var inside it
	by cancatenate while inside quotes until find a $ and then take 
		the Var NAME after it, if it valid then will expand it */
char	*handle_d_q_var(char *str, int *index, t_infos *infos)
{
	char	*result;
	char	*tmp;
	int		start;

	start = *index;
	result = ft_strdup("");
	while (str && str[*index] && str[*index] != '"')
	{
		if (special_vars(&result, &str, &start, index) && (*index)++)
			continue ;
		if (str[*index] == '$' && str[*index + 1] != '$'
			&& !ft_isdigit(str[*index + 1]) && str[*index + 1] != '"')
		{
			take_previous(&result, str, start, (*index));
			(*index)++;
			tmp = expand_variable(str, index, infos);
			result = ft_strjoin(result, tmp);
			free(tmp);
			start = *index;
		}
		else
			d_q_var_part2(&result, str, &start, index);
	}
	take_previous(&result, str, start, (*index));
	return ((*index)++, result);
}

/* this func work when there is an single quotes so it will
	concatenate around the string until find 
			the closed quotes */
char	*handle_s_q_var(char *str, int *index)
{
	char	*result;
	int		start;

	start = (*index);
	while (str[*index] && str[*index] != '\'')
		(*index)++;
	result = ft_strndup(str + start, *index - start);
	(*index)++;
	return (result);
}

int	normal_var(char **result, char *word, int tab[], t_infos *infos)
{
	char	*tmp;
	int		flag;

	flag = 0;
	if (word[(tab[0])] == '$' && word[(tab[0]) + 1] != '$'
		&& (ft_isalnum(word[(tab[0]) + 1])
			|| word[(tab[0]) + 1] == '_' || word[(tab[0]) + 1] == '?'))
	{
		flag = 1;
		take_previous(result, word, tab[1], (tab[0]));
		(tab[0])++;
		tmp = expand_variable(word, &tab[0], infos);
		tmp = remove_var_spaces(tmp);
		*result = ft_strjoin(*result, tmp);
		free(tmp);
		(tab[1]) = (tab[0]);
	}
	return (flag);
}

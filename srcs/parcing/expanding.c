/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmraizik <hmraizik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 05:02:53 by hmraizik          #+#    #+#             */
/*   Updated: 2024/10/15 11:30:53 by hmraizik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes_cases(char **result, char *word, int tab[], t_infos *infos)
{
	char	*tmp;
	int		flag;

	flag = 0;
	if (word && word[tab[0]] == '\'')
	{
		take_previous(result, word, tab[1], tab[0]);
		tab[1] = ++(tab[0]);
		tmp = handle_s_q_var(word, &tab[0]);
		*result = ft_strjoin(*result, tmp);
		free(tmp);
		tab[1] = (tab[0]);
		flag = 1;
	}
	else if (word && word[tab[0]] == '"')
	{
		take_previous(result, word, tab[1], tab[0]);
		tab[1] = ++(tab[0]);
		tmp = handle_d_q_var(word, &tab[0], infos);
		*result = ft_strjoin(*result, tmp);
		free(tmp);
		tab[1] = tab[0];
		flag = 2;
	}
	return (flag);
}

static int	is_it_special_var(char **result, char *word, int tab[])
{
	if (word[tab[0]] == '$' && word[tab[0] + 1] != '$' && (special_vars
			(result, &word, &tab[1], &tab[0]) != 0 && tab[0]++))
		return (1);
	return (0);
}

int	handle_var_part2(char **result, char *word, int tab[])
{
	if (is_it_special_var(result, word, tab))
		return (1);
	else if (double_dollar_cases(result, word, tab))
		return (1);
	else
		return (0);
}

/*this func check the case of var, if it inside quotes or not...
	and deppend on this it expand it or not*/
char	*handle_var(t_list *tmp, int heredoc_flag, t_infos *infos, char *buffer)
{
	char	*result;
	char	*word;
	int		tab[2];

	word = buffer;
	if (!buffer && tmp)
		word = tmp->content;
	result = ft_strdup("");
	initial_ints(&tab[0], &tab[1], NULL);
	while (word && word[tab[0]])
	{
		if (!heredoc_flag && quotes_cases(&result, word, tab, infos))
			tmp->type = VAR;
		else if (handle_var_part2(&result, word, tab))
			continue ;
		else if (normal_var(&result, word, tab, infos))
		{
			if (tmp && tmp->type != VAR)
				tmp->type = NORMAL_VAR;
			continue ;
		}
		else
			tab[0]++;
	}
	return (take_previous(&result, word, tab[1], tab[0]), result);
}

/*in this func will looping around all the tokenz and detect is the 
	an var exist, if it then pass it to handle_var to expand
					if it a valid var */
void	expanding(t_list **head, t_infos *infos)
{
	t_list	*tmp;
	char	*tmp2;

	tmp = *head;
	if (!head || !tmp)
		return ;
	while (tmp)
	{
		if (tmp->content && ft_strchr((tmp->content), '~'))
		{
			tmp2 = tmp->content;
			tmp->content = handle_home_symbol(tmp->content, infos);
			tmp->type = VAR;
			free(tmp2);
		}
		else if (tmp->content && tmp->type == WORD
			&& ft_strchr(tmp->content, '$') && *(ft_strchr
				(tmp->content, '$') + 1) && (ft_isalnum(*(ft_strchr
						(tmp->content, '$') + 1)) || accepted_chars(tmp))
			&& tmp->type != DELEMETRE)
			update_content(tmp, infos);
		tmp = tmp->next;
	}
}

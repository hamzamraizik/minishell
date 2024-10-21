/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmraizik <hmraizik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:41:31 by ochangli          #+#    #+#             */
/*   Updated: 2024/10/17 08:12:51 by hmraizik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

/*this funtion free the node that was removed from the env list*/
void	free_unsettled_node(t_my_env	*node)
{
	free(node->variable);
	free(node->data);
	free(node);
}

/*this function search in the env struct until find the var name,
	the remove it's node from the list and free it*/
int	unset_it(char *variable, t_infos *infos)
{
	t_my_env	*tmp;
	t_my_env	*prev;
	int			flag;

	tmp = infos->bash_env;
	prev = NULL;
	flag = 0;
	while (tmp)
	{
		if (ft_strncmp(tmp->variable, variable, ft_strlen(variable) + 1) == 0)
		{
			if (prev)
				prev->next = tmp->next;
			else
				infos->bash_env = tmp->next;
			free_unsettled_node(tmp);
			flag = 1;
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	infos->envp = env_list_to_array(infos->bash_env, infos->envp);
	return (flag);
}

/*this function check if the name of variable is valid to process it or not*/
int	not_valid_variable(char *str)
{
	int	i;

	i = 0;
	if (str && !ft_isalpha(str[0]) && str[0] != '_')
		return (1);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

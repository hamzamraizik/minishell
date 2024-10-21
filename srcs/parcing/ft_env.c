/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochangli <ochangli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 06:12:06 by hmraizik          #+#    #+#             */
/*   Updated: 2024/10/18 00:52:40 by ochangli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*this func when a var expanded, replaced with it
 	real value in the env if it exist, if not exist
		then it will replaced by '\0'*/
char	*expand_variable(char *str, int *index, t_infos *infos)
{
	char	*result;
	int		name_length;
	int		var_len;
	char	*name;
	int		i;

	i = *index;
	initial_ints(&name_length, &var_len, NULL);
	result = NULL;
	if (str[i] == '?' && (*index)++)
		return (ft_itoa(infos->exit_status));
	while (str[i] && str[i] != ' '
		&& (ft_isalnum(str[i]) || str[i] == '_') && i++)
		name_length++;
	name = malloc((name_length + 1) * sizeof(char));
	if (!name)
		return (write(2, "malloc failed!\n", 15), NULL);
	while (ft_isalnum(str[*index]) || str[*index] == '_')
	{
		name[var_len] = str[*index];
		var_len++;
		(*index)++;
	}
	name[var_len] = '\0';
	return (result = my_getenv_var(name, infos), free(name), result);
}

//this function get variable value from the my env
char	*my_getenv_var(char *name, t_infos *infos)
{
	t_my_env	*tmp;

	tmp = infos->bash_env;
	while (tmp)
	{
		if (tmp->data && !ft_strncmp(tmp->variable, name, ft_strlen(name) + 1))
			return (ft_strdup(tmp->data));
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

static int	ft_lstsize2(t_my_env *lst)
{
	int			count;
	t_my_env	*next;

	count = 0;
	next = lst;
	if (!lst)
		return (0);
	while (next != NULL)
	{
		count++;
		next = next->next;
	}
	return (count);
}

char	**env_list_to_array(t_my_env *env, char **envp_tab)
{
	int			i;
	t_my_env	*tmp;

	i = 0;
	if (envp_tab)
		free_substrs(envp_tab);
	envp_tab = malloc((ft_lstsize2(env) + 1) * sizeof(char *));
	if (!envp_tab)
		return (NULL);
	tmp = env;
	while (tmp)
	{
		envp_tab[i] = ft_strdup(tmp->variable);
		if (!envp_tab[i])
			return (free(envp_tab), NULL);
		envp_tab[i] = ft_strjoin(envp_tab[i], "=");
		if (!envp_tab[i])
			return (NULL);
		if (tmp->data)
			envp_tab[i] = ft_strjoin(envp_tab[i], tmp->data);
		tmp = tmp->next;
		i++;
	}
	envp_tab[i] = NULL;
	return (envp_tab);
}

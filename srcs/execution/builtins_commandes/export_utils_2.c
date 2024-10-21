/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmraizik <hmraizik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:49:34 by ochangli          #+#    #+#             */
/*   Updated: 2024/10/17 08:08:32 by hmraizik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	not_valid_identifier(char *str, t_infos *infos)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	if (!*str)
		return (export_fails(str, infos), 1);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (export_fails(str, infos), 1);
	while (str[i] && (str[i] != '=' && !(str[i] == '+' && str[i + 1] == '=')))
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (export_fails(str, infos), 1);
		i++;
	}
	return (0);
}

void	sort_infos_env(t_my_env	*infos)
{
	t_my_env	*tmp;
	t_my_env	*tmp2;
	char		*tmp_variable;
	char		*tmp_data;

	tmp = infos;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (ft_strncmp(tmp->variable, tmp2->variable,
					ft_strlen(tmp->variable)) > 0)
			{
				tmp_variable = tmp->variable;
				tmp_data = tmp->data;
				tmp->variable = tmp2->variable;
				tmp->data = tmp2->data;
				tmp2->variable = tmp_variable;
				tmp2->data = tmp_data;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}

int	is_alredy_exist(char *variable, t_infos *infos)
{
	t_my_env	*tmp;

	tmp = infos->bash_env;
	while (tmp)
	{
		if (ft_strncmp(tmp->variable, variable, ft_strlen(variable) + 1) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	update_in_env(char *variable, char *data, t_infos *infos)
{
	t_my_env	*tmp;
	int			flag;
	char		*tmp_adrr;

	tmp = infos->bash_env;
	flag = 0;
	while (tmp)
	{
		if (ft_strncmp(tmp->variable, variable, ft_strlen(variable) + 1) == 0)
		{
			tmp_adrr = tmp->data;
			tmp->data = data;
			free(tmp_adrr);
			tmp_adrr = NULL;
			flag = 1;
			free(variable);
			variable = NULL;
			break ;
		}
		tmp = tmp->next;
	}
	if (flag == 0)
		ft_lstadd_back_exec(&infos->bash_env, ft_lstnew_exec(variable, data));
	infos->envp = env_list_to_array(infos->bash_env, infos->envp);
}

t_my_env	*copy_env(t_my_env	*env)
{
	t_my_env	*tmp;
	t_my_env	*new_env;

	tmp = env;
	new_env = NULL;
	while (tmp)
	{
		ft_lstadd_back_exec(&new_env, ft_lstnew_exec(tmp->variable, tmp->data));
		tmp = tmp->next;
	}
	return (new_env);
}

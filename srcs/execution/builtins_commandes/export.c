/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochangli <ochangli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:45:25 by ochangli          #+#    #+#             */
/*   Updated: 2024/10/17 23:13:57 by ochangli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	clear_env(t_my_env	*env)
{
	t_my_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp);
	}
}

/*this function just print env variables with exported variables*/
int	print_export_table(t_infos *infos)
{
	t_my_env	*env_copy;
	t_my_env	*tmp_env;

	env_copy = copy_env(infos->bash_env);
	sort_infos_env(env_copy);
	tmp_env = env_copy;
	while (tmp_env)
	{
		if (tmp_env->variable && !tmp_env->data)
			printf("declare -x %s\n", tmp_env->variable);
		else if (tmp_env->variable && tmp_env->data)
			printf("declare -x %s=\"%s\"\n", tmp_env->variable, tmp_env->data);
		tmp_env = tmp_env->next;
	}
	clear_env(env_copy);
	return (1);
}

void	export_process(char *var_str, char *data_str, char *cmd, t_infos *infos)
{
	if (var_str && var_str[0]
		&& (!valid_to_add_it(cmd)) && !is_alredy_exist(var_str, infos))
	{
		free(data_str);
		data_str = NULL;
	}
	update_in_env(var_str, data_str, infos);
}

void	just_print_export(t_cmd *data, t_infos *infos)
{
	if (!data->cmd[1])
		print_export_table(infos);
	infos->exit_status = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochangli <ochangli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 10:00:05 by ochangli          #+#    #+#             */
/*   Updated: 2024/10/17 23:18:39 by ochangli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	change_pwd(t_infos *infos)
{
	char	*new_pwd;

	update_in_env(ft_strdup("OLDPWD"), get_from_myenv(
			ft_strdup("PWD"), infos), infos);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		perror("minishell: cd:");
		return ;
	}
	else
		update_in_env(ft_strdup("PWD"), new_pwd, infos);
}

int	deleted_dir(t_cmd *data)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd: "
			"cannot access parent directories: No such file or directory\n", 2);
		chdir(data->cmd[1]);
		free(pwd);
		pwd = NULL;
		return (1);
	}
	return (free(pwd), 0);
}

int	cd_builtin_exec(t_cmd *data, t_infos *infos)
{
	char	*path;

	if (data->cmd[1] && !data->cmd[1][0])
		return (0);
	else if (!data->cmd[1])
	{
		path = get_from_myenv(ft_strdup("HOME"), infos);
		if ((chdir(path)) == -1)
			return (free(path), ft_putstr_fd
				("minishell:  cd: HOME not set\n", 2), 1);
		change_pwd(infos);
		return (free(path), 0);
	}
	else if (deleted_dir(data))
		return (1);
	else if (chdir(data->cmd[1]) == -1 && write(2, "cd: ", 4))
		return ((ft_putstr_fd(data->cmd[1], 2), perror(" ")), 1);
	else
		change_pwd(infos);
	return (0);
}

int	pwd_builtin_exec(t_cmd *data, t_infos *infos)
{
	char	*path_ptr;

	(void)data;
	path_ptr = get_from_myenv(ft_strdup("PWD"), infos);
	if (!path_ptr)
	{
		perror("minishell: pwd:");
		return (1);
	}
	ft_putstr_fd(path_ptr, 1);
	ft_putstr_fd("\n", 1);
	free(path_ptr);
	return (0);
}

int	export_builtin_exec(t_cmd *data, t_infos *infos, int i)
{
	char	*variable_str;
	char	*data_str;

	just_print_export(data, infos);
	while (++i && data->cmd && data->cmd[i])
	{
		if (not_valid_identifier(data->cmd[i], infos))
			continue ;
		variable_str = get_variable(data->cmd[i]);
		if (!variable_str)
			return (1);
		data_str = get_data(data->cmd[i], infos);
		if (data_str && !data_str[0] && !valid_to_add_it
			(data->cmd[i]) && is_alredy_exist(variable_str, infos))
		{
			(free(variable_str), free(data_str));
			continue ;
		}
		export_process(variable_str, data_str, data->cmd[i], infos);
	}
	return (infos->exit_status);
}

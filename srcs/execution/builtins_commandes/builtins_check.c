/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochangli <ochangli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 08:51:26 by ochangli          #+#    #+#             */
/*   Updated: 2024/10/18 16:20:35 by ochangli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	is_builtin_cmd_exec(char *cmd)
{
	int		i;
	char	*builtins[7];

	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	if (!cmd)
		return (1);
	i = 0;
	while (i < 6)
	{
		if (ft_strcmp_exec(cmd, builtins[i], 1) == 0)
			return (0);
		i++;
	}
	if (ft_strcmp_exec(cmd, builtins[i], 0) == 0)
		return (0);
	return (1);
}

/*This function execute the right builtin commande*/
int	builtin_cmds_exec(t_cmd	*data, t_infos *infos, int is_onecmd)
{
	int	cmd_status;

	cmd_status = 0;
	if (!ft_strcmp_exec(data->cmd[0], "env", 1))
		cmd_status = env_builtin_exec(data, infos);
	else if (!ft_strcmp_exec(data->cmd[0], "echo", 1))
		cmd_status = exex_echo_exec(data, infos);
	else if (!ft_strcmp_exec(data->cmd[0], "pwd", 1))
		cmd_status = pwd_builtin_exec(data, infos);
	else if (!ft_strcmp_exec(data->cmd[0], "export", 1))
		cmd_status = export_builtin_exec(data, infos, 0);
	else if (!ft_strcmp_exec(data->cmd[0], "unset", 1))
		cmd_status = unset_builtin_exec(data, infos);
	else if (!ft_strcmp_exec(data->cmd[0], "cd", 1))
		cmd_status = cd_builtin_exec(data, infos);
	else if (!ft_strncmp(data->cmd[0], "exit", 4))
		cmd_status = exit_builtin_exec(data, infos, is_onecmd);
	update_exit_status(infos, cmd_status);
	return (cmd_status);
}

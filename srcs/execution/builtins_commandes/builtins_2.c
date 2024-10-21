/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochangli <ochangli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 10:08:48 by ochangli          #+#    #+#             */
/*   Updated: 2024/10/18 03:32:04 by ochangli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

/*this function used to remove variables from the env*/
int	unset_builtin_exec(t_cmd *data, t_infos *infos)
{
	int	i;

	i = 1;
	infos->exit_status = 0;
	if (!data->cmd[1])
		return (0);
	while (data->cmd[i])
	{
		if (not_valid_variable(data->cmd[i]))
		{
			infos->exit_status = 1;
			unset_fails(data->cmd[i], infos);
			i++;
			continue ;
		}
		if (is_alredy_exist(data->cmd[i], infos))
			unset_it(data->cmd[i], infos);
		i++;
	}
	return (infos->exit_status);
}
/*****************************************************************************/

int	is_nemeric(char *string)
{
	int	i;

	i = 0;
	while (string[i] == ' ' || string[i] == '\t')
		i++;
	if ((string[i] == '+' || string[i] == '-'))
		i++;
	while (string[i] && ft_isdigit(string[i]))
		i++;
	while (string[i] == ' ' || string[i] == '\t')
		i++;
	if (string[i] != '\0')
		return (0);
	return (1);
}

int	exit_builtin_exec(t_cmd	*data, t_infos *infos, int is_onecmd)
{
	long long int	num;

	if (is_onecmd)
		ft_putstr_fd("exit\n", 1);
	if (!data->cmd[1])
		exit(infos->exit_status);
	if (!is_nemeric(data->cmd[1]) || !data->cmd[1][0])
	{
		ft_putstr_fd("Minishell: exit:", 2);
		ft_putstr_fd(data->cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	if (data->cmd[1] && !data->cmd[2])
	{
		num = ft_atoi(data->cmd[1]);
		if (num == -1 && ft_strncmp(data->cmd[1], "9223372036854775807", 19))
			(ft_putstr_fd("Minishell: exit: ", 2), ft_putstr_fd(data->cmd[1]
					, 2), ft_putstr_fd(" : numeric argument required\n", 2));
		exit(num);
	}
	else
		return (ft_putstr_fd("minishell: exit: too many arguments\n", 2), 1);
	return (0);
}

/*****************************************************************************/
/*This function is used to print The envirement variables */
int	env_builtin_exec(t_cmd *data, t_infos *infos)
{
	t_my_env	*tmp;

	(void)data;
	tmp = infos->bash_env;
	while (tmp != NULL)
	{
		if (tmp->variable && tmp->data)
			printf("%s=%s\n", tmp->variable, tmp->data);
		tmp = tmp->next;
	}
	return (0);
}

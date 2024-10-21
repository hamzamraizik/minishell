/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmraizik <hmraizik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:02:39 by ochangli          #+#    #+#             */
/*   Updated: 2024/10/17 08:11:43 by hmraizik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	ft_putstr_fd_exec(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	return ;
}

/*This functionis called to execute echo if it is 
with the flag "-n" */
void	exex_echo_no_flag_exec(char **echo_cmd)
{
	int	i;

	i = 1;
	while (echo_cmd[i] != NULL)
	{
		ft_putstr_fd_exec(echo_cmd[i], 1);
		if (echo_cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}

int	is_just_n(char *str)
{
	int	i;

	i = 1;
	while (str && str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

/*This functionis called to execute echo if it is 
without the flag "-n" */
void	exex_echo_with_flag_exec(char **echo_cmd)
{
	int	i;

	i = 2;
	while (echo_cmd[i] && (!ft_strncmp(echo_cmd[i], "-n", 2)
			&& is_just_n(echo_cmd[i])))
		i++;
	while (echo_cmd[i] != NULL)
	{
		ft_putstr_fd_exec(echo_cmd[i], 1);
		if (echo_cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
}

/*This function is called if the commande is "echo" , and redirect
Thr function depending on the echo flag -n*/
int	exex_echo_exec(t_cmd	*data, t_infos *infos)
{
	if (data->cmd[1] && (!ft_strncmp(data->cmd[1], "-n", 2)
			&& is_just_n(data->cmd[1])))
		exex_echo_with_flag_exec(data->cmd);
	else if (data->cmd[1] && (!ft_strcmp_exec(data->cmd[1], "$?", 0)))
		printf("%d\n", infos->exit_status);
	else
		exex_echo_no_flag_exec(data->cmd);
	return (0);
}

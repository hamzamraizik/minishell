/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochangli <ochangli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 07:01:45 by ochangli          #+#    #+#             */
/*   Updated: 2024/10/18 17:52:39 by ochangli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

/*this function check if the file is a directory or not*/
int	is_directory(char	*commande)
{
	t_file_type	file_infos;

	stat(commande, &file_infos);
	if (S_ISDIR(file_infos.st_mode))
		return (0);
	else if (S_ISREG(file_infos.st_mode))
		return (2);
	return (1);
}

/*This function call execve tp  execute
	the executable commande*/
void	execve_commande(t_cmd *data, t_infos *infos)
{
	char	*bash_cmd;

	bash_cmd = get_cmd_exec(data->cmd[0], infos->envp);
	if (!bash_cmd)
		return ;
	execve(bash_cmd, data->cmd, infos->envp);
	no_file_or_dir_exec(data->cmd[0]);
}

/*This function return the addresse of a variable
	name , from the envirement list*/
char	*get_var_from_env(t_my_env *env, char *variable)
{
	t_my_env	*tmp;

	tmp = env;
	while (tmp->variable)
	{
		if (!ft_strmycmp(tmp->variable, variable))
			return (tmp->data);
		tmp = tmp->next;
	}
	return (NULL);
}

/*This function is used if there is only one commande */
void	one_single_commande(t_cmd *data, t_infos *infos)
{
	pid_t	child;

	if (!is_builtin_cmd_exec(data->cmd[0]))
		builtin_cmds_exec(data, infos, 1);
	else
	{
		child = fork();
		if (child == -1)
			perror("fails to cret the child: ");
		else if (child == 0)
			execve_commande(data, infos);
		get_status(child, infos, 1);
	}
}

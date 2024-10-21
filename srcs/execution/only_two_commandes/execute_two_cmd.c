/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_two_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochangli <ochangli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 07:01:32 by ochangli          #+#    #+#             */
/*   Updated: 2024/10/18 03:32:22 by ochangli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	close_two_pipes(int pipe[2])
{
	close(pipe[0]);
	close(pipe[1]);
	return ;
}

/*This commande will be called when th user have two commandes */
void	two_commandes(t_cmd *data, t_infos *infos)
{
	int	status;

	if (!is_builtin_cmd_exec(data->cmd[0]))
	{
		status = builtin_cmds_exec(data, infos, 0);
		exit(status);
	}
	else
		execve_commande(data, infos);
}

/*in two commandes case , this function used to fork the first child */
int	fork_first_child(t_cmd *data, t_infos *infos, int pp[])
{
	pid_t	child_1;

	child_1 = fork();
	if (child_1 == -1)
	{
		perror("minishell :Fails to creat first child ");
		return (-1);
	}
	else if (child_1 == 0)
	{
		close(pp[0]);
		if (dup2(pp[1], STDOUT_FILENO) == -1)
		{
			perror("Fails to creat dup the firsst pipe");
			return (-1);
		}
		close(pp[1]);
		if (files_and_redirections(data, infos) == -1)
			exit (1);
		two_commandes(data, infos);
	}
	return (child_1);
}

/*in two commandes case , this function used to fork the second child */
int	fork_second_child(t_cmd *data, t_infos *infos, int pp[])
{
	pid_t	child_2;

	child_2 = fork();
	if (child_2 == -1)
	{
		perror("minishell :Fails to creat second child ");
		return (-1);
	}
	else if (child_2 == 0)
	{
		close(pp[1]);
		if (dup2(pp[0], STDIN_FILENO) == -1)
		{
			perror("fails to creat dup The second pipe");
			return (-1);
		}
		close(pp[0]);
		data = data->next;
		if (files_and_redirections(data, infos) == -1)
			exit (1);
		two_commandes(data, infos);
	}
	return (child_2);
}

/*Start two commandes execution */
void	execute_two_cmd(t_cmd *data, t_infos *infos)
{
	int		pp[2];
	pid_t	childs[2];

	if (pipe(pp) == -1)
		return (perror("pipes error "));
	childs[0] = fork_first_child(data, infos, pp);
	if (childs[0] == -1)
	{
		close_two_pipes(pp);
		perror("fails to execute The first commnade");
		return ;
	}
	childs[1] = fork_second_child(data, infos, pp);
	if (childs[1] == -1)
	{
		close_two_pipes(pp);
		perror("fails to execute The sexond commnade");
		return ;
	}
	close_two_pipes(pp);
	wait_all(childs, infos, 2);
}

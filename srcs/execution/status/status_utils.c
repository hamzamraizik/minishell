/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochangli <ochangli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 13:57:41 by ochangli          #+#    #+#             */
/*   Updated: 2024/10/17 07:25:02 by ochangli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

/*This function used to updtae the exit status variable from
	The struct*/
void	update_exit_status(t_infos *infos, int exit_num)
{
	infos->exit_status = exit_num;
	return ;
}

/*This function get the status of a child process */
void	get_status(int pid, t_infos *infos, int flg)
{
	int	wait_status;

	wait_status = 0;
	waitpid(pid, &wait_status, 0);
	if (WIFEXITED(wait_status))
	{
		infos->exit_status = WEXITSTATUS(wait_status);
		return ;
	}
	else if (WIFSIGNALED(wait_status))
	{
		if (WTERMSIG(wait_status) == SIGQUIT && flg == 1)
			printf("Quit 3\n");
		infos->exit_status = 128 + WTERMSIG(wait_status);
	}
}

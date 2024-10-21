/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochangli <ochangli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 10:08:43 by ochangli          #+#    #+#             */
/*   Updated: 2024/10/18 14:53:04 by ochangli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*This function return the size of the list*/
int	ft_lstsize(void *lst)
{
	int		count;
	t_cmd	*next;

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

/*This function return The originals STDIN and STDOUT
	streams */
int	return_origin_streams(int *origin_fds)
{
	if (dup2(origin_fds[0], STDIN_FILENO) == -1)
		dup_fails(1);
	close(origin_fds[0]);
	if (dup2(origin_fds[1], STDOUT_FILENO) == -1)
		dup_fails(1);
	close(origin_fds[1]);
	return (0);
}

/*This function duplicate The STDIN and STDOUT to back them later*/
int	dup_out_in(int *orinal_fds)
{
	int	fd_in;
	int	fd_out;

	fd_in = dup(STDIN_FILENO);
	if (fd_in == -1)
		dup_fails(1);
	fd_out = dup(STDOUT_FILENO);
	if (fd_out == -1)
	{
		close(fd_in);
		dup_fails(1);
	}
	orinal_fds[0] = fd_in;
	orinal_fds[1] = fd_out;
	return (0);
}
/*THis function free respources when the commande fails*/

void	free_commande_ress(int *tmp_fds)
{
	close(tmp_fds[0]);
	close(tmp_fds[1]);
}

/*from This function The execution Start*/
void	initial_execution(t_cmd	*data, t_infos	*infos)
{
	int	cmds_nbr;
	int	origin_fds[2];

	signal(SIGQUIT, quit_handler);
	g_signal = 1;
	if (dup_out_in(origin_fds) == -1)
		return ;
	if (!data->cmd[0] && !data->next && !data->files.allfiles)
		return (free_commande_ress(origin_fds));
	cmds_nbr = ft_lstsize(data);
	if (cmds_nbr == 1)
	{
		if (files_and_redirections(data, infos) == -1)
			return (free_commande_ress(origin_fds));
		one_single_commande(data, infos);
	}
	else if (cmds_nbr == 2)
		execute_two_cmd(data, infos);
	else
		execute_multiple_cmds(data, infos, cmds_nbr);
	if (return_origin_streams(origin_fds) == -1)
		return (dup_fails(0));
}

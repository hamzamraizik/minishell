/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlp_cmd_alloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochangli <ochangli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 07:03:11 by ochangli          #+#    #+#             */
/*   Updated: 2024/10/17 07:03:12 by ochangli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

/*This function is for the first child allocation*/
pid_t	creat_first_child(t_cmd	*data, t_infos *infos, int	**pp, int *inf)
{
	pid_t	child_1;
	int		dup;

	child_1 = fork();
	if (child_1 == -1)
		return (-1);
	else if (child_1 == 0)
	{
		dup = dup_first_child(pp, inf);
		if (dup == -1)
			dup_fails(1);
		if (files_and_redirections(data, infos) == -1)
			exit (1);
		two_commandes(data, infos);
	}
	return (child_1);
}

/*This function is for the midlle childs allocation*/
pid_t	creat_midlle_childs(t_cmd	*data, t_infos *infos, int	**pp, int *inf)
{
	pid_t	child;
	int		dup;

	child = fork();
	if (child == -1)
		return (-1);
	else if (child == 0)
	{
		dup = dup_midlle_child(pp, inf);
		if (dup == -1)
			dup_fails(2);
		if (files_and_redirections(data, infos) == -1)
			exit (1);
		two_commandes(data, infos);
	}
	return (child);
}

/*This function is for the last childs allocation*/
int	creat_last_child(t_cmd	*data, t_infos *infos, int	**pp, int *inf)
{
	pid_t	child_2;
	int		dup;

	child_2 = fork();
	if (child_2 == -1)
		return (-1);
	else if (child_2 == 0)
	{
		dup = dup_last_child(pp, inf);
		if (dup == -1)
			dup_fails(3);
		if (files_and_redirections(data, infos) == -1)
			exit (1);
		two_commandes(data, infos);
	}
	return (child_2);
}

void	build_commande_env_multiple(t_cmd	*data, t_infos	*info)
{
	int	files_index[2];
	int	in_out_fd[2];

	init_files_index(data->files, files_index);
	init_fds_index(in_out_fd);
	if (creat_files(data->files.allfiles, data->files, info) == 1)
		return (update_exit_status(info, 1));
	if (file_opening(data, in_out_fd, files_index) == -1)
	{
		perror("minishell :");
		return (update_exit_status(info, 1));
	}
	if (redirect_commnde(in_out_fd[0], in_out_fd[1]) == -1)
	{
		perror("minishell :");
		return (update_exit_status(info, 1));
	}
	two_commandes(data, info);
}

void	execute_multiple_cmds(t_cmd *data, t_infos *infos, int cmd_number)
{
	int		**pp;
	pid_t	*childs;
	int		inf[3];

	if (initila_and_alloc(inf, cmd_number, &childs, &pp) == 1)
		return ;
	childs[0] = creat_first_child(data, infos, pp, inf);
	if (childs[0] == -1)
		return (child_fails(childs, pp, cmd_number - 1));
	(1) && (close(pp[0][1]), data = data->next);
	while (++inf[2] < cmd_number - 1)
	{
		inf[0] = inf[2];
		childs[inf[2]] = creat_midlle_childs(data, infos, pp, inf);
		if (childs[inf[2]] == -1)
			return (child_fails(childs, pp, cmd_number - 1));
		(1) && close_child_pipes(pp, inf[0]), (data = data->next);
	}
	inf[0] = inf[2];
	childs[inf[2]] = creat_last_child(data, infos, pp, inf);
	if (childs[inf[2]] == -1)
		child_fails(childs, pp, cmd_number - 1);
	(1) && close(pp[inf[2] - 1][0]), wait_all(childs, infos, cmd_number);
	free(childs);
	free_allocated_pipes(pp, cmd_number - 1);
}

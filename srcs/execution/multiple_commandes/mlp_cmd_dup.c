/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlp_cmd_dup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochangli <ochangli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 07:04:25 by ochangli          #+#    #+#             */
/*   Updated: 2024/10/17 07:04:29 by ochangli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

/*This function used to dup for The first child */
int	dup_first_child(int	**pp, int *inf)
{
	close_all_pipes(pp, inf);
	close(pp[inf[0]][0]);
	if (dup2(pp[inf[0]][1], STDOUT_FILENO) == -1)
		return (-1);
	close(pp[inf[0]][1]);
	return (0);
}

/*This function used to dup for The midlle child */

int	dup_midlle_child(int **pp, int	*inf)
{
	close_all_pipes(pp, inf);
	close(pp[inf[0]][0]);
	close(pp[inf[0] - 1][1]);
	if (dup2(pp[inf[0] - 1][0], STDIN_FILENO) == -1)
		return (-1);
	close(pp[inf[0] - 1][0]);
	if (dup2(pp[inf[0]][1], STDOUT_FILENO) == -1)
		return (-1);
	close(pp[inf[0]][1]);
	return (0);
}

/*This function used to dup for The last child */
int	dup_last_child(int	**pp, int	*inf)
{
	close_all_pipes(pp, inf);
	close(pp[inf[0] - 1][1]);
	if (dup2(pp[inf[0] - 1][0], STDIN_FILENO) == -1)
		return (-1);
	close (pp[inf[0] - 1][0]);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlp_cmd_err.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochangli <ochangli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 07:04:37 by ochangli          #+#    #+#             */
/*   Updated: 2024/10/17 23:15:11 by ochangli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

/*This function print error when child creation fails*/
void	child_fails(pid_t *childs, int **pp, int pipe_num)
{
	close_pipes(pp, pipe_num);
	free_allocated_pipes(pp, pipe_num);
	free(childs);
	perror("fails to creat child :");
	return ;
}

/*This function print error when child dup fails*/
void	dup_fails(int status)
{
	if (status == 0)
		perror("dup fails :");
	else if (status == 1)
		perror("first dup fails :");
	else if (status == 2)
		perror("second dup fails :");
	else
		perror("last dup fails :");
	exit(1);
}

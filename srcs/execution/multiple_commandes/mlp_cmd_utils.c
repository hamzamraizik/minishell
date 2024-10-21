/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlp_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochangli <ochangli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 03:47:11 by ochangli          #+#    #+#             */
/*   Updated: 2024/10/17 23:15:27 by ochangli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

/*This function allocate memory for pipes array*/
int	**allocate_memory_for_pipes(int pipes)
{
	int	**pp;
	int	i;

	i = 0;
	pp = malloc((pipes) * sizeof(int *));
	if (!pp)
		return (NULL);
	while (i < pipes)
	{
		pp[i] = malloc(sizeof(int) * 2);
		if (!pp[i])
			return (NULL);
		if (pipe(pp[i]) == -1)
		{
			free_int_array((void **)pp, i);
			return (perror("pipes fails :"), NULL);
		}
		i++;
	}
	return (pp);
}

/*This function close the non used ends of pipes in the child*/
int	close_child_pipes(int **pp, int index)
{
	close(pp[index - 1][0]);
	close(pp[index][1]);
	return (0);
}

void	cmd_infos_init(int	*cmd_inf, int num)
{
	cmd_inf[0] = 0;
	cmd_inf[1] = num;
}

/*This function called when the creation of midlle childs fails*/
void	midlle_childs_fails(t_infos	*infos, int	**pp, int cmd_number)
{
	perror("minishell: fork: ");
	free_allocated_pipes(pp, cmd_number - 1);
	update_exit_status(infos, 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlp_cmd_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochangli <ochangli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:09:08 by ochangli          #+#    #+#             */
/*   Updated: 2024/10/17 07:29:37 by ochangli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	*allocate_for_childs(int cmd_number)
{
	pid_t	*childs;
	int		i;

	i = 0;
	childs = malloc((cmd_number) * sizeof(pid_t));
	if (!childs)
		return (NULL);
	return (childs);
}

/*This function used to allocate memory for th pipes array
    and the childs array*/
int	initila_and_alloc(int *cmd_infos, int cmd_number,
						int **childs, int ***pipes)
{
	*pipes = NULL;
	*childs = NULL;
	cmd_infos[0] = 0;
	cmd_infos[1] = cmd_number;
	cmd_infos[2] = 0;
	*childs = allocate_for_childs(cmd_number);
	if ((*childs) == NULL)
		return (1);
	*pipes = allocate_memory_for_pipes(cmd_number - 1);
	if ((*pipes) == NULL)
	{
		free_int_array((void **)childs, cmd_number);
		return (1);
	}
	return (0);
}

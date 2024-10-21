/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlp_cmd_clean.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochangli <ochangli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 07:02:05 by ochangli          #+#    #+#             */
/*   Updated: 2024/10/17 07:26:59 by ochangli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

/*This function is used to close all pipes not used by a child*/
void	close_all_pipes(int **pp, int *inf)
{
	int	i;
	int	j;
	int	end;

	i = 0;
	j = 0;
	end = inf[1] - 1;
	while (i < end)
	{
		j = 0;
		if ((i == inf[0]) || (i == inf[0] - 1))
		{
			i++;
			continue ;
		}
		while (j < 2)
		{
			close(pp[i][j]);
			j++;
		}
		i++;
	}
}

/*this function close all pipes in the parent process*/
void	close_pipes(int **pp, int nbr)
{
	int	i;
	int	j;

	i = 0;
	while (i < nbr)
	{
		j = 0;
		while (j < 2)
		{
			close(pp[i][j]);
			j++;
		}
		i++;
	}
}

/*This function free memory allocated for pipes array*/
void	free_allocated_pipes(int **pp, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(pp[i]);
		i++;
	}
	free(pp);
	return ;
}

/*This function wait the child until the before last one*/
void	wait_all(int *childs, t_infos *infos, int cmd_number)
{
	int	i;

	i = 0;
	while (i < cmd_number)
	{
		if (i == cmd_number - 1)
			get_status(childs[i], infos, 1);
		else
			get_status(childs[i], infos, 0);
		i++;
	}
	return ;
}

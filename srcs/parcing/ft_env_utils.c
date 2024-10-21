/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmraizik <hmraizik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:12:05 by hmraizik          #+#    #+#             */
/*   Updated: 2024/10/15 11:32:30 by hmraizik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*if error happens in main and it should returns,
    so this fuction will free the env infos that
    initialized at start
*/
void	free_lists(t_infos *infos)
{
	t_my_env	*tmp;
	t_my_env	*tmp2;

	if (!infos->bash_env)
		return ;
	tmp = infos->bash_env;
	while (tmp)
	{
		free(tmp->variable);
		free(tmp->data);
		tmp->data = NULL;
		tmp->variable = NULL;
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2);
	}
	free_substrs(infos->envp);
	infos->envp = NULL;
	free(infos);
}

/*after handle_var() fuction returns the actual values of 
    the all variables names in tmp->content, from the env,
    this fuction replace the content with the returned content
    , and free the old
*/
void	update_content(t_list *tmp, t_infos *infos)
{
	char	*tmp2;
	int		real_exit_status;

	real_exit_status = infos->exit_status;
	if (tmp->content && ft_strchr(tmp->content, '$')
		&& *(ft_strchr(tmp->content, '$') + 1) == '?' && pipe_before(tmp))
		infos->exit_status = 0;
	tmp2 = tmp->content;
	tmp->content = handle_var(tmp, 0, infos, NULL);
	if (tmp->type != NORMAL_VAR)
		tmp->type = VAR;
	free(tmp2);
	infos->exit_status = real_exit_status;
}

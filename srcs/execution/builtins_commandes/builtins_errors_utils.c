/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_errors_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmraizik <hmraizik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 04:02:34 by hmraizik          #+#    #+#             */
/*   Updated: 2024/10/17 07:13:38 by hmraizik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

/*This fnuction is called to print unset errors in stdrr
	in case it fails */
void	unset_fails(char *str, t_infos *infos)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	update_exit_status(infos, 1);
}

/*This function is called whenever export fails */

void	export_fails(char *str, t_infos *infos)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	update_exit_status(infos, 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmraizik <hmraizik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:45:22 by ochangli          #+#    #+#             */
/*   Updated: 2024/10/17 08:12:34 by hmraizik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	valid_to_add_it(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' || (str[i] == '+' && str[i + 1] == '='))
			return (1);
		i++;
	}
	return (0);
}

char	*get_variable(char *string)
{
	int		i;
	char	*variable;

	i = 0;
	if (!string)
		return (NULL);
	while (string[i] && string[i] != '='
		&& ft_strncmp(string + i, "+=", 2) != 0)
		i++;
	variable = malloc(sizeof(char) * i + 1);
	if (!variable)
		return (NULL);
	i = 0;
	while (string[i] && string[i] != '='
		&& ft_strncmp(string + i, "+=", 2) != 0)
	{
		variable[i] = string[i];
		i++;
	}
	variable[i] = '\0';
	return (variable);
}

char	*get_from_myenv(char *variable, t_infos *infos)
{
	t_my_env	*tmp;

	tmp = infos->bash_env;
	while (tmp)
	{
		if (variable && ft_strncmp(tmp->variable, variable,
				ft_strlen(variable) + 1) == 0
			&& tmp->data)
			return (free(variable), ft_strdup(tmp->data));
		tmp = tmp->next;
	}
	return (free(variable), ft_strdup(""));
}

void	joint_data(char **data, char *string, t_infos *infos)
{
	char	*tmp;
	char	*tmp2;

	tmp = *data;
	tmp2 = get_from_myenv(get_variable(string), infos);
	*data = ft_strjoin(tmp2, *data);
	free(tmp);
	tmp = NULL;
}

char	*get_data(char *string, t_infos *infos)
{
	int		i;
	int		j;
	char	*data;
	int		is_plus;

	initial_ints(&i, &j, &is_plus);
	if (!string)
		return (NULL);
	while (string && string[i] && string[i] != '=')
	{
		if (string[i] == '+' && string[i + 1] == '=')
			is_plus = 1;
		i++;
	}
	(string[i]) && (i++);
	data = malloc(sizeof(char) * (ft_strlen(string) - i) + 1);
	if (!data)
		return (NULL);
	while (string[i])
		data[j++] = string[i++];
	data[j] = '\0';
	if (is_plus == 1)
		joint_data(&data, string, infos);
	return (data);
}

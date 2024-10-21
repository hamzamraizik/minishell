/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_list_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmraizik <hmraizik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:48:51 by hmraizik          #+#    #+#             */
/*   Updated: 2024/10/16 23:25:47 by hmraizik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_quotes(char *s)
{
	int		i;
	int		j;
	int		is_quote;
	char	*new;

	i = 0;
	j = 0;
	is_quote = 0;
	new = malloc(ft_strlen(s) + 1 * sizeof(char));
	if (!new)
		return (NULL);
	while (s[i])
	{
		is_quote = check_quotes(is_quote, s[i]);
		if ((is_quote != 2 && s[i] == '\'') || (is_quote != 1 && s[i] == '\"'))
			i++;
		else
			new[j++] = s[i++];
	}
	new[j] = '\0';
	return (free(s), s = NULL, new);
}

char	*trim_name_quotes(char *s, int type)
{
	int		i;
	int		j;
	int		is_quote;
	char	*new;

	initial_ints(&i, &j, &is_quote);
	if (type == VAR || type == NORMAL_VAR)
		return (ft_strdup(s));
	new = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!new)
		return (write(2, "malloc failed in trim_quotes!\n", 30), NULL);
	while (s && s[i])
	{
		is_quote = check_quotes(is_quote, s[i]);
		if ((is_quote != 2 && s[i] == '\'') || (is_quote != 1 && s[i] == '\"'))
			i++;
		else
			new[j++] = s[i++];
	}
	new[j] = '\0';
	return (new);
}

int	fill_cmd(t_list *tmp, char **cmd)
{
	if (tmp->content && (ft_strchr(tmp->content, '\'')
			|| ft_strchr(tmp->content, '\"')) && tmp->type != VAR
		&& tmp->type != NORMAL_VAR)
	{
		if (tmp->type != VAR)
			tmp->content = trim_quotes(tmp->content);
		*cmd = ft_strdup(tmp->content);
		if (!*cmd)
			return (1);
	}
	else
	{
		*cmd = ft_strdup(tmp->content);
		if (!*cmd)
			return (1);
	}
	return (0);
}

void	terminate_files(t_files *files, int *index)
{
	files->infiles[index[0]] = NULL;
	files->outfiles[index[1]] = NULL;
	files->appendfiles[index[2]] = NULL;
	files->delemetre[index[3]] = NULL;
	files->allfiles[index[4]] = NULL;
	files->ambiguous_indexes[index[5]] = -1;
}

void	free_files(t_files *files)
{
	int	i;

	i = 0;
	while (files->infiles && files->infiles[i])
		free(files->infiles[i++]);
	i = 0;
	while (files->outfiles && files->outfiles[i])
		free(files->outfiles[i++]);
	i = 0;
	while (files->appendfiles && files->appendfiles[i])
		free(files->appendfiles[i++]);
	i = 0;
	while (files->allfiles && files->allfiles[i])
		free(files->allfiles[i++]);
	i = 0;
	while (files->delemetre && files->delemetre[i])
		free(files->delemetre[i++]);
}

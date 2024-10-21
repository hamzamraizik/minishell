/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochangli <ochangli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 07:02:46 by hmraizik          #+#    #+#             */
/*   Updated: 2024/10/18 03:44:52 by ochangli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../execution/execution.h"

int	parse_line(char *line, t_list **head, t_cmd **cmd, t_infos *infos)
{
	char	**new_line;
	int		length;

	length = ft_strlen(line);
	*head = NULL;
	*cmd = NULL;
	new_line = NULL;
	line = add_delimetre(line, length);
	if (!line)
		return (1);
	new_line = ft_new_split(line, '\0', length);
	if (!new_line && write(2, "malloc failed!\n", 15))
		return (1);
	if (tokenizing(head, new_line))
		return (free_substrs(new_line), 1);
	if (syntax_error(*head) == 1)
		return (infos->exit_status = 258, 1);
	expanding(head, infos);
	*cmd = fill_cmds_list(head);
	if (!*cmd)
		return (1);
	if (ft_heredoc(*cmd, infos))
		return (1);
	return (0);
}

int	ft_start(t_list **head, t_cmd **cmd_lst, t_infos *infos, t_termios *term)
{
	char	*line;
	char	*new_line;

	while (1 && isatty(0))
	{
		line = readline("Minishell -> ");
		if (!line)
			return (ft_putstr_fd("exit\n", 1), 0);
		sig_int_status(infos);
		if (add_line_to_history(line, infos))
			continue ;
		new_line = add_spaces(line, count_new_len(line, ft_strlen(line)));
		if (!new_line)
			return (free(line), 1);
		if (parse_line(new_line, head, cmd_lst, infos)
			&& free_things(new_line, line, *head))
			continue ;
		(g_signal) && (infos->exit_status = 1);
		if (g_signal != 1)
			initial_execution(*cmd_lst, infos);
		refresh_stat(new_line, line, *head, term);
		clear_cmds_list(cmd_lst);
	}
	return (0);
}

t_infos	*inistialize_cmd_infos(char **envp)
{
	t_infos	*infos;

	infos = malloc(sizeof(t_infos));
	if (!infos)
		return (NULL);
	infos->exit_status = 0;
	infos->bash_env = NULL;
	infos->envp = NULL;
	get_bash_env_exec(&infos->bash_env, envp);
	infos->envp = env_list_to_array(infos->bash_env, infos->envp);
	return (infos);
}

int	main(int argc, char **argv, char **envp)
{
	t_list		*head;
	t_cmd		*cmd_lst;
	t_infos		*infos;
	t_termios	term;
	int			g_signal;

	g_signal = 0;
	(void)argc, (void)argv;
	tcgetattr(0, &term);
	infos = inistialize_cmd_infos(envp);
	head = NULL;
	cmd_lst = NULL;
	signals();
	if (ft_start(&head, &cmd_lst, infos, &term) == 1)
		return (free_lists(infos), rl_clear_history(), 1);
	return (free_lists(infos), rl_clear_history(), 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmraizik <hmraizik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:49:47 by hmraizik          #+#    #+#             */
/*   Updated: 2024/10/17 07:01:10 by hmraizik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_hedroc(int signo)
{
	(void)signo;
	g_signal = 1;
	close(0);
	printf("\n");
}

void	sig_handler(int signo)
{
	if (signo == SIGINT && g_signal != 1)
	{
		g_signal = 2;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	quit_handler(int sig_num)
{
	(void)sig_num;
	return ;
}

void	signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	rl_catch_signals = 0;
}

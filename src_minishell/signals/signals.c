/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:02:25 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/27 13:27:59 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"
#include <signal.h>

/*
*	init_minishell -> signals_interactive_mode
*	when executing non_builtin command -> signals_non_interactive_mode
*		-> call signals_interactive_mode after child_process finished
*/

extern int last_signal_received;

void	interactive_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		last_signal_received = SIGINT_RECEVEID;
	}
}

void	signals_interactive_mode(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &interactive_handler;
	sigaction(SIGINT, &act, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	non_interactive_handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		printf("\n");
		last_signal_received = SIGINT_RECEVEID;
	}
	else if (signal == SIGQUIT)
	{
		rl_on_new_line();
		printf("Quit (core dumped)\n");
		last_signal_received = SIGQUIT_RECEIVED;
	}
}

void	signals_non_interactive_mode(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = non_interactive_handler;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

void	refresh_signal(t_config *minishell)
{
	if (last_signal_received == SIGQUIT_RECEIVED)
		minishell->last_error_code = SIGQUIT_RECEIVED;
	else if (last_signal_received == SIGINT_RECEVEID)
		minishell->last_error_code = SIGINT_RECEVEID;
	last_signal_received = AWAITING_SIGNAL;
}

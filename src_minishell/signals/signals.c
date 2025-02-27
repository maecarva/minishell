/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:02:25 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/27 12:04:44 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"


/*
*	init_minishell -> signals_interactive_mode
*	when executing non_builtin command -> signals_non_interactive_mode
*		-> call signals_interactive_mode after child_process finished
*/

void	interactive_handler(int	signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signals_interactive_mode(void)
{
	struct sigaction        act;

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
	}
	else if (signal == SIGQUIT)
	{
		rl_on_new_line();
		printf("Quit (core dumped)\n");
	}
}

void	signals_non_interactive_mode(void)
{
	struct sigaction        act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = non_interactive_handler;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

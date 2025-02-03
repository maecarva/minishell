/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:02:25 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/03 17:56:51 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"
#include <readline/readline.h>


void	signals_handler(int	signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_signals(void)
{
	struct sigaction        act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &signals_handler;
	sigaction(SIGINT, &act, NULL);
	sigemptyset(&act.sa_mask);
	signal(SIGQUIT, SIG_IGN);
}

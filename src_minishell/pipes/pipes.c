/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:10:04 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/27 11:55:17 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

// void	check_children(t_pipes *p_data)
// {
// 	pid_t	pid;
// 	int		status;
// 	int		exit_code;

// 	pid = 1;
// 	while (pid > 0)
// 	{
// 		pid = waitpid(-1, &status, 0);
// 		if (pid == -1 && errno != ECHILD)
// 			ft_perror("waitpid", ERROR_CODE);
// 		exit_code = WEXITSTATUS(status);
// 		if (exit_code == ERROR_CODE)
// 			p_data->ms_data->last_error_code = ERROR_CODE;
// 		if (pid == p_data->pid_last_parent)
// 		{
// 			if (exit_code == ERROR_COMMAND || exit_code == ERROR_CODE
// 				|| exit_code == EXIT_FAILURE || exit_code == CFBNE
// 				|| exit_code == 2)
// 			{
// 				if (p_data->ms_data->last_error_code != ERROR_CODE)	
// 				p_data->ms_data->last_error_code = exit_code;
// 			}
// 			else
// 				p_data->ms_data->last_error_code = 0;
// 		}
// 	}
// }

void	check_children(t_pipes *p_data)
{
	pid_t	pid;
	int		status;
	int		exit_code;

	pid = 1;
	if (p_data->do_not_wait == true)
		return ;
	while (pid > 0)
	{
		pid = waitpid(-1, &status, 0);
		exit_code = WEXITSTATUS(status);
		if (exit_code == ERROR_CODE)
			p_data->ms_data->last_error_code = ERROR_CODE;
		if (pid == p_data->pid_last_parent)
		{
			if (p_data->ms_data->last_error_code != ERROR_CODE)
			{
				p_data->ms_data->last_error_code = exit_code;
				if (exit_code == 214)
					p_data->ms_data->last_error_code = 1;
			}
		}
	}
}

void	pipes(t_config *ms_data)
{
	t_pipes	p_data;

	signals_non_interactive_mode();
	init_p_data(&p_data, ms_data);
	if (p_data.nb_pipes == 0)
		simple_command(&p_data);
	else
	{
		first_parent(&p_data);
		infinite_parent(&p_data);
		last_parent(&p_data);
	}
	check_children(&p_data);
	signals_interactive_mode();
}

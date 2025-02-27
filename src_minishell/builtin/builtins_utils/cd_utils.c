/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:41:01 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/26 21:50:04 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_minishell/minishell.h"

void	print_cd_err(char *message, t_config *minishell)
{
	ft_putstr_fd(message, 2);
	minishell->last_error_code = 1;
}

void	print_cd_errs(char *msg1, char *msg2, char *msg3, t_config *minishell)
{
	error_message(msg1, msg2, msg3);
	minishell->last_error_code = 1;
}

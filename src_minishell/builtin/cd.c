/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:16:59 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/11 18:28:13 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

void	execute_cd(char *cmd, t_config *minishell)
{
	int	i;

	if (!cmd)
		return ;
	i = 0;
	if (ft_count_char_in_str(cmd, ' ') >= 2)
	{
		minishell->last_error_code = 1;
		ft_putstr_fd(" too many arguments\n", 2);
		return ;
	}
	while (cmd[i] && !ft_isspace(cmd[i]))
		i++;
	while (cmd[i] && ft_isspace(cmd[i]))
		i++;
	if (chdir(&cmd[i]) == -1)
	{
		ft_putstr_fd(" no such file or directory\n", 2);
		minishell->last_error_code = 1;
	}
	minishell->last_error_code = 0;
}

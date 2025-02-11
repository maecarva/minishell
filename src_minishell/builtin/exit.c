/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:54:27 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/11 17:46:32 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

bool	all_alpha(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (ft_isdigit(cmd[i]))
			return (false);
		i++;
	}
	return (true);
}
void	execute_exit(char *cmd, t_config *minishell)
{
	int	exit_code;
	int	i;
	int	sign;

	if (!minishell || !cmd)
		return ;
	i = 0;
	sign = 1;
	if (all_alpha(cmd))
	{
		ft_putstr_fd(" numeric argument required\n", 2);
		exit_code = 2;
	}
	else if (ft_count_char_in_str(cmd, ' ') >= 2)
	{
		exit_code = 1;
		ft_putstr_fd(" too many arguments\n", 2);
	}
	else
	{
		while (cmd[i] && (ft_isalpha(cmd[i]) || ft_isspace(cmd[i])))
			i++;
		while (cmd[i] && !ft_isdigit(cmd[i]))
		{
			if (cmd[i] == '-')
				sign *= -1;
			i++;
		}
		exit_code = ft_atoi(&cmd[i]);
	}
	clear_minishell(minishell);
	exit(exit_code * sign);
}

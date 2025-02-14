/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:16:52 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/14 16:30:20 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	get_echo_flag(char *cmd, int *i)
{
	bool	flag;
	int		k;

	k = 5;
	flag = false;
	while (cmd[k])
	{
		while (ft_isspace(cmd[k]) == 1)
			k++;
		*i = k;
		if (cmd[k] != '-')
			break;
		k++;
		while (cmd[k] == 'n')
			k++;
		if (!((cmd[k] == '\0' || ft_isspace(cmd[k]) == 1) && cmd[k - 1] == 'n'))
			break;
		if (flag == false)
			flag = true;
		*i = k;
	}
	return (flag);
}

void	execute_echo(char *cmd, t_config *ms_data)
{
	int		i;
	bool	flag;

	i = 5;
	flag = get_echo_flag(cmd, &i);
	if (flag == false)
		printf("%s\n", (cmd + i));
	else
		printf("%s", (cmd + i));
	ms_data->last_error_code = 0;
}

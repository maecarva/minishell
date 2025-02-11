/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:16:52 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/11 18:34:15 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	get_echo_flag(char *cmd, int *i)
{
	int		k;
	bool	flag;

	k = 0;
	flag = false;
	while (ft_isspace(cmd[k]) == 0 && cmd[k] != 'n' && cmd[k] != '-')
	{
		ft_skip_spaces(cmd, &k);
		if (cmd[k] == '-')
			k++;
		while (cmd[*i] == 'n')
			k++;
		if (ft_isspace(cmd[*i]) == 0)
			return (flag);
		*i = k;
		flag = true;

	}
	return (flag);
}

void	echo(t_config *ms_data)
{
	int		i;
	bool	flag;

	i = 0;
	flag = get_echo_flag(((t_node2 *)(ms_data->ast->item))->command, &i);
	if (flag == false)
		printf("%s\n", ((t_node2 *)(ms_data->ast->item))->command);
	else
		printf("%s", ((t_node2 *)(ms_data->ast->item))->command);
}

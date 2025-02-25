/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:16:52 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/21 15:15:23 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

void	execute_echo(char **cmd, t_config *minishell)
{
	bool	flag;
	int		i;
	char	*tmp;

	flag = false;
	i = 1;
	if (!cmd || !minishell)
		return ;
	if (cmd[i] && ft_strncmp(cmd[i], "-n", ft_strlen("-n")) == 0 && ft_str_is_only_charset(&cmd[i][1], "n"))
	{
		flag = true;
		while (cmd[i] && ft_strncmp(cmd[i], "-n", ft_strlen("-n")) == 0 && ft_str_is_only_charset(&cmd[i][1], "n"))
			i++;
	}
	if (tab_size(cmd) == 2 && flag == false && ft_strncmp(cmd[i], "-n", ft_strlen("-n")) == 0)
	{
		tmp = &cmd[i][0];
		if (ft_isspace(*tmp))
		{
			while (*tmp && ft_isspace(*tmp))
				tmp++;
			flag = true;
		}
		else {
			tmp = cmd[i];
		}
		printf("%s", tmp);
	}
	else if (tab_size(cmd) >= 2)
	{
		while (cmd[i])
		{
			printf("%s", cmd[i]);
			i++;
			if (cmd[i])
				printf(" ");
		}
	}
	if (flag == false)
		printf("\n");
	minishell->last_error_code = 0;
}

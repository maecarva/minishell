/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:16:59 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/15 17:51:45 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

int	tab_size(char **splited)
{
	int	i;

	if (!splited || !*splited)
		return (0);
	i = 0;
	while (splited[i])
		i++;
	return (i);
}

void	execute_cd(char *cmd, t_config *minishell)
{
	char	**splited;

	if (!cmd || !minishell)
		return ;
	splited = ft_split_charset(cmd, WHITESPACES);
	if (!splited)
		return ;
	if (tab_size(splited) >= 3)
	{
		minishell->last_error_code = 1;
		ft_putstr_fd(" too many arguments\n", 2);
		return ;
	}
	else if (tab_size(splited) == 1)
	{
		if (chdir(get_value_by_name(minishell->environnement, "HOME")) == -1)
		{
			ft_putstr_fd("bash: cd: HOME not set", 2);
			minishell->last_error_code = 1;
			return ;
		}
	}
	else if (tab_size(splited) > 1 && chdir(splited[1]) == -1)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(splited[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		minishell->last_error_code = 1;
		return ;
	}
	else
		minishell->last_error_code = 0;
}

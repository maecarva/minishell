/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:31:41 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/26 21:58:44 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

void	execute_pwd(char **cmd, t_config *minishell)
{
	char	path[MAX_PATH];
	char	*pathbis;

	ft_bzero(path, MAX_PATH);
	if (!cmd)
		return ;
	if (getcwd(path, MAX_PATH) == path)
		printf("%s\n", path);
	else
	{
		pathbis = get_value_by_name(minishell->environnement, "PWD");
		if (pathbis)
			printf("%s\n", pathbis);
		free(pathbis);
	}
	minishell->last_error_code = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:38:45 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/08 18:26:59 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

char	*get_value_by_name(char **envp, char *name)
{
	int		i;
	char	*value;
	char	*tmp;

	i = 0;
	value = NULL;
	tmp = NULL;
	if (!envp)
		return (NULL);
	if (ft_strlen(name) == 0)
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp(name, envp[i], ft_strlen(name)) == 0)
		{
			tmp = ft_strchr(envp[i], '=') + 1;
			if (!tmp)
				return (NULL);
			value = ft_strdup(tmp);
			if (!value)
				return (NULL);
			return (value);
		}
		i++;
	}
	return (NULL);
}

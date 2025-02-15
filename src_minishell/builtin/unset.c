/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:47:45 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/15 18:58:11 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

char	**duplicate_env_without_var(char *varname, t_config *minishell)
{
	char	**env;
	int		i;
	int		j;
	int		new_size;
	size_t	len;

	if (!varname || !minishell)
		return (NULL);
	len = ft_strlen(varname);
	// Calculer le nombre de variables restantes (en excluant celle à supprimer)
	i = 0;
	new_size = 0;
	while (minishell->environnement[i])
	{
		if (!(ft_strncmp(minishell->environnement[i], varname, len) == 0
			&& minishell->environnement[i][len] == '='))
			new_size++;
		i++;
	}
	// Allouer le nouveau tableau (new_size entrées + 1 pour le NULL)
	env = ft_calloc(new_size + 1, sizeof(char *));
	if (!env)
		return (NULL);
	// Copier les variables non concernées
	i = 0;
	j = 0;
	while (minishell->environnement[i])
	{
		if (ft_strncmp(minishell->environnement[i], varname, len) == 0
			&& minishell->environnement[i][len] == '=')
		{
			// Ne pas copier la variable à supprimer
			i++;
			continue;
		}
		env[j] = ft_strdup(minishell->environnement[i]);
		j++;
		i++;
	}
	env[j] = NULL;
	return (env);
}





void	execute_unset(char *cmd, t_config *minishell)
{
	int		i;
	char	**splited;
	char	**envdup;

	if (!cmd || !minishell)
		return ;
	splited = ft_split_charset(cmd, WHITESPACES);
	if (!splited || !*splited)
		return ;
	i = 1;
	while (splited[i])
	{
		envdup = duplicate_env_without_var(splited[i], minishell);
		if (!envdup)
			break ;
		// Libérer l'ancien environnement pour éviter une fuite mémoire
		ft_free_double_ptr(&minishell->environnement);
		minishell->environnement = envdup;
		i++;
	}
	ft_free_double_ptr(&splited);
}


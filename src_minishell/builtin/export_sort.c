/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:36:57 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/27 14:31:02 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_min_index(char **env, int start)
{
	int	min_index;
	int	i;

	min_index = start;
	i = start;
	while (env[i])
	{
		if (ft_strcmp(env[min_index], env[i]) > 0)
			min_index = i;
		i++;
	}
	return (min_index);
}

static void	print_sorted_env(char **env)
{
	int		n;
	int		i;
	int		j;
	bool	passed;

	n = tab_size(env);
	i = 0;
	while (i < n)
	{
		passed = false;
		printf("declare -x ");
		j = 0;
		while (env[i][j])
		{
			printf("%c", env[i][j]);
			if (env[i][j] == '=' && passed == false)
			{
				passed = true;
				printf("\"");
			}
			j++;
		}
		i++;
		printf("\"\n");
	}
}

void	char_swap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void	export_sort(t_config *minishell)
{
	int		i;
	int		min_index;
	char	**env;
	int		n;

	n = tab_size(minishell->environnement);
	env = ft_tabdup(minishell->environnement);
	if (!env)
	{
		minishell->last_error_code = ERROR_CODE;
		clear_minishell(minishell);
	}
	i = 0;
	while (i < n)
	{
		min_index = find_min_index(env, i);
		if (min_index != i)
			char_swap(&(env[i]), &(env[min_index]));
		i++;
	}
	print_sorted_env(env);
	ft_free_double_ptr(&env);
	minishell->last_error_code = 0;
}

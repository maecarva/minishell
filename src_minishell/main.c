/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:05:52 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/03 10:06:30 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_minishell/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_minishell	*minishell;

	minishell = init(ac, av, env);
	return (0);
}

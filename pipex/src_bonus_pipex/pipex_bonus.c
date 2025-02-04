/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:11:51 by ebonutto          #+#    #+#             */
/*   Updated: 2025/01/28 14:33:31 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	pipex_bonus(t_pipex data)
{
	first_parent(data);
	mid_parent(data);
	last_parent(&data);
	check_children(data);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;

	if (argc < 5 || (ft_strncmp(argv[1], "here_doc", 8) == 0 && argc < 6))
		ft_error("Invalid Number Of Arguments", EXIT_FAILURE);
	data = init_pipex_bonus(argc, argv, envp);
	pipex_bonus(data);
	return (0);
}

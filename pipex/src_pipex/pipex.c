/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:17:15 by ebonutto          #+#    #+#             */
/*   Updated: 2025/01/29 15:39:14 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(t_pipex data)
{
	first_parent(data);
	close((data.fd)[0][1]);
	last_parent(&data);
	check_children(data);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;

	if (argc != 5)
		ft_error("Invalid Number Of Arguments", EXIT_FAILURE);
	data = init_pipex(argc, argv, envp);
	pipex(data);
	return (0);
}

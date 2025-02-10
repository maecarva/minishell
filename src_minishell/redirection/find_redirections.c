/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:00:24 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/10 15:09:53 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_infile(t_btree *cmd1, t_pipes *p_data)
{
	p_data->fd_infile = 0;
	while (cmd1->left != NULL)
	{
		cmd1 = cmd1->left;
		p_data->fd_infile = open(((t_node2 *)(cmd1->item))->file, O_RDONLY, 0644);
		if (p_data->fd_infile == -1)
			perror("open");
		if (cmd1->left != NULL)
			close(p_data->fd_infile);
	}
}

void	get_outfile(t_btree *cmdn, t_pipes *p_data) // ne pas oublier de checker les acces pour les differents outfile, voir s'ils existent deja et s'ils sont ouvrables...
{
	int	flags;

	p_data->fd_outfile = 1;
	print_arbre(cmdn, 0);
	while (cmdn->left != NULL)
	{
		cmdn = cmdn->left;
		if (((t_node2 *)(cmdn->item))->type == TRUNCATE)
			flags = O_WRONLY | O_CREAT | O_TRUNC;
		else if (((t_node2 *)(cmdn->item))->type == APPEND)
			flags = O_WRONLY | O_CREAT | O_APPEND;
		p_data->fd_outfile = open(((t_node2 *)(cmdn->item))->file, flags, 0644);
		if (p_data->fd_infile == -1)
			perror("open");
		if (cmdn->left != NULL)
			close(p_data->fd_outfile);
	}
}

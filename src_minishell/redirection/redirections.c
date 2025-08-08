/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:10:11 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/25 11:17:09 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_redirections(t_pipes *p_data)
{
	t_lexertok	type;
	t_btree		*cmd;

	cmd = p_data->ms_data->ast;
	while (cmd->left != NULL)
	{
		cmd = cmd->left;
		type = ((t_node2 *)(cmd->item))->type;
		if (type == REDIRECT_INPUT || type == HEREDOC)
		{	
			if (get_infile(p_data, cmd) == 1)
				return (1);
		}
		else
		{
			if (get_outfile(p_data, cmd) == 1)
				return (1);
		}
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 12:34:48 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/27 13:27:55 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_name_here_doc(t_config *minishell, t_btree *cmd, int *i)
{
	char	*name;
	char	*number;

	while (1)
	{
		number = ft_itoa(*i);
		if (!number)
		{
			minishell->last_error_code = ERROR_CODE;
			clear_minishell(minishell);
		}
		name = ft_strjoin("/tmp/here_doc_", number);
		if (!name)
		{
			free(number);
			minishell->last_error_code = ERROR_CODE;
			clear_minishell(minishell);
		}
		(*i)++;
		free(number);
		if (access(name, F_OK) != 0)
			break ;
		free(name);
	}
	((t_node2 *)(cmd->item))->file = name;
}

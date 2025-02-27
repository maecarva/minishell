/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:22:26 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/27 14:24:49 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include_minishell/minishell.h"

int	count_groups(t_dlist *start, t_dlist *end)
{
	t_dlist	*tmp;
	int		groups;

	if (!start || !end)
		return (0);
	if (start == end)
		return (0);
	tmp = start;
	groups = 0;
	while (tmp)
	{
		if (ptr_to_lexertoklist(tmp->content)->type == PARENTHESIS_L)
			groups++;
		tmp = tmp->next;
		if (tmp == end)
			break ;
	}
	return (groups);
}

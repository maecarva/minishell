/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:46:18 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/04 16:42:35 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

int	count_pipes(t_btree	*arbre)
{
	int	count;

	return (1);
	if (!arbre)
		return (0);
	count = 0;
	while (arbre || ft_strcmp("|", (char *)arbre->item) != 0)
	{
		count++;
		arbre = arbre->right;
	}
	return (count);
}

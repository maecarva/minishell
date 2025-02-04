/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:14:26 by ebonutto          #+#    #+#             */
/*   Updated: 2024/11/12 10:03:51 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Prototype
	void ft_lstclear(t_list **lst, void (*del)(void *));

Description
	Deletes and frees the given element and every
	successor of that element, using the function ’del’
	and free(3).
	Finally, the pointer to the list must be set to
	NULL.

Parameters
	#1. The adress of a pointer to an element.
	#2. The adress of the function used to delete the
	content of the element.

Return value
	None
*/

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
	*lst = NULL;
}

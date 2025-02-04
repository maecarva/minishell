/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:14:19 by ebonutto          #+#    #+#             */
/*   Updated: 2024/11/12 09:42:19 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Prototype
	void ft_lstadd_back(t_list **lst, t_list *new);

Description
	Adds the element ’new’ at the end of the list.
	The function ft_lstadd_back adds a new node to the back of a list:
		[1]->[2]->[3]->[NEW]->[NULL]

Parameters
	#1. The address of a pointer to the first link of
	a list.
	#2. The address of a pointer to the element to be
	added to the list.

Return value
	None
*/

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	ft_lstlast(*lst)->next = new;
}

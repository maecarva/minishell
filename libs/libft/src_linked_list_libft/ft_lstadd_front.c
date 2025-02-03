/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: x03phy <x03phy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:14:24 by ebonutto          #+#    #+#             */
/*   Updated: 2025/01/02 01:17:47 by x03phy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Prototype
	void ft_lstadd_front(t_list **lst, t_list *new);

Description
	Adds the element ’new’ at the beginning of the
	list.
	The function ft_lstadd_front adds a new node to the front of a list:
		[NEW]->[1]->[2]->[3]->[NULL]

Parameters
	#1. The address of a pointer to the first link of
	a list.
	#2. The address of a pointer to the element to be
	added to the list.

Return value
	None
*/

void	ft_lstadd_front(t_list **head, t_list *new)
{
	if (!new)
		return ;
	if (!(*head))
	{
		*head = new;
		return ;
	}
	new->next = *head;
	*head = new;
}

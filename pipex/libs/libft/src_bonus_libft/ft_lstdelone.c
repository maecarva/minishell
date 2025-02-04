/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:14:29 by ebonutto          #+#    #+#             */
/*   Updated: 2024/11/12 10:05:02 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Prototype
	void ft_lstdelone(t_list *lst, void (*del)(void *));

Description
	Takes as a parameter an element and frees the
	memory of the element’s content using the function
	’del’ given as a parameter and free the element.
	The memory of ’next’ must not be freed.

Parameters
	#1. The element to free.
	#2. The address of the function used to delete the
	content.

Return value
	None
*/

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:14:32 by ebonutto          #+#    #+#             */
/*   Updated: 2024/11/12 10:07:29 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Prototype
	void ft_lstiter(t_list *lst, void (*f)(void *));

Description
	Iterates the list ’lst’ and applies the function
	’f’ to the content of each element.

Parameters
	#1. The adress of a pointer to an element.
	#2. The adress of the function used to iterate on
	the list.

Return value
	None
*/

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

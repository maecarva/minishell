/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:03:10 by maecarva          #+#    #+#             */
/*   Updated: 2024/12/24 15:05:28 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_libft/libft.h"

t_dlist	*dll_new(void *content)
{
	t_dlist	*new;

	new = ft_calloc(sizeof(t_dlist), 1);
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:15:07 by ebonutto          #+#    #+#             */
/*   Updated: 2024/11/12 11:31:24 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Prototype
	void ft_putstr_fd(char *s, int fd);

Description
	Outputs the string ’s’ to the given file
	descriptor.

Parameters
	#1. The string to output.
	#2. The file descriptor on which to write.

Return value
	None
*/

void	ft_putstr_fd(char *s, int fd)
{
	size_t	count;

	if (!s)
		return ;
	count = 0;
	while (s[count])
	{
		ft_putchar_fd(s[count], fd);
		count++;
	}
}

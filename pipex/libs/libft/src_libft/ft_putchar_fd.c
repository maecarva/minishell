/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:15:00 by ebonutto          #+#    #+#             */
/*   Updated: 2024/11/12 11:30:59 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Prototype
	void ft_putchar_fd(char c, int fd);

Description
	Outputs the character ’c’ to the given file
	descriptor.

Parameters
	#1. The character to output.
	#2. The file descriptor on which to write.

Return value
	None
*/

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

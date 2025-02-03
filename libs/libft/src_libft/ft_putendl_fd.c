/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: x03phy <x03phy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:15:02 by ebonutto          #+#    #+#             */
/*   Updated: 2025/01/05 23:51:03 by x03phy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Prototype
	void ft_putendl_fd(char *s, int fd);

Description
	Outputs the string ’s’ to the given file
	descriptor, followed by a newline.

Parameters
	#1. The string to output.
	#2. The file descriptor on which to write.

Return value
	None
*/

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

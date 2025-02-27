/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:48:04 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/27 15:20:43 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include_minishell/minishell.h"

void	get_files(char ***joined, int *num, bool hidden, char *pwd)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = NULL;
	dir = opendir(pwd);
	if (!dir)
		return (ft_free_double_ptr(joined));
	entry = readdir(dir);
	while (entry != NULL && num[0] < 250)
	{
		if (entry->d_name[0] != '.' || hidden == true)
		{
			(*joined)[num[0]] = ft_strdup(entry->d_name);
			if ((*joined)[num[0]] == NULL)
				return (closedir(dir), ft_free_double_ptr(joined));
			num[0]++;
		}
		entry = readdir(dir);
	}
	joined[num[0]] = NULL;
	closedir(dir);
}

/*
*	num[] 0: i, 1: tabsize
*/
char	**get_all_files(bool hidden)
{
	char			pwd[MAX_PATH];
	char			**joined;
	int				num[2];

	num[0] = 0;
	num[1] = 250;
	joined = ft_calloc(sizeof(char *), num[1]);
	if (!joined)
		return (false);
	ft_bzero(pwd, MAX_PATH);
	if (getcwd(pwd, MAX_PATH) != pwd)
		return (NULL);
	get_files(&joined, num, hidden, pwd);
	if (!joined)
		return (NULL);
	return (joined);
}

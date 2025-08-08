/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 20:05:44 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/27 15:18:07 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include_minishell/minishell.h"

int	match_pattern(char *file, char *pattern)
{
	if (!file || !pattern)
		return (0);
	while (*file == '*')
		file++;
	if (*pattern == '\0')
		return (*file == '\0');
	if (*pattern == '*')
	{
		while (*(pattern + 1) == '*')
			pattern++;
		if (*(pattern + 1) == '*')
			return (1);
		while (*file)
		{
			if (match_pattern(file, pattern + 1))
				return (1);
			file++;
		}
		return (match_pattern(file, pattern + 1));
	}
	else if (*pattern == *file)
		return (match_pattern(file + 1, pattern + 1));
	return (0);
}

char	**search_for_matching_files(char **cmd, char *pattern)
{
	char	**files;
	char	**validfiles;
	int		i;
	int		j;

	if (!cmd || !*cmd || !pattern)
		return (free(pattern), NULL);
	if (pattern[0] == '.')
		files = get_all_files(true);
	else
		files = get_all_files(false);
	if (!files)
		return (free(pattern), NULL);
	validfiles = ft_calloc(sizeof(char *), tab_size(files) + 1);
	if (!validfiles)
		return (ft_free_double_ptr(&files), free(pattern), NULL);
	i = -1;
	j = -1;
	while (files[++i])
		if (match_pattern(files[i], pattern))
			validfiles[++j] = ft_strdup(files[i]);
	if (tab_size(validfiles) == 0)
		ft_free_double_ptr(&validfiles);
	return (ft_free_double_ptr(&files), free(pattern), validfiles);
}

char	**expand_wildcard_pls(char **cmd, int *i, bool *quotes)
{
	char	**files;
	int		start;
	int		end;

	files = NULL;
	if ((*cmd)[*i] == '\"')
		quotes[1] = !quotes[1];
	if ((*cmd)[*i] == '\'')
		quotes[0] = !quotes[0];
	if ((*cmd)[*i] == '*' && no_quotes(quotes))
	{
		start = *i;
		while (start > 0 && !ft_isspace((*cmd)[start - 1]))
			start--;
		end = *i;
		while ((*cmd)[end] && !ft_isspace((*cmd)[end]))
			end++;
		if (end - start == 1)
			files = get_all_files(false);
		else
			files = search_for_matching_files(cmd,
					ft_substr(*cmd, start, end - start));
		*i = end;
	}
	return (files);
}

// 0 : single, 1 : double
char	**expand_wildcards(char	**cmd)
{
	bool	quotes[2];
	int		i;
	char	**files;

	if (!*cmd || ft_count_char_in_str(*cmd, '*') == 0)
		return (NULL);
	clean_quotes(cmd);
	i = 0;
	files = NULL;
	quotes[0] = false;
	quotes[1] = false;
	while ((*cmd)[i])
	{
		files = expand_wildcard_pls(cmd, &i, quotes);
		if (files)
			break ;
		i++;
	}
	return (files);
}

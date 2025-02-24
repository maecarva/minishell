/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:14:29 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/23 19:24:32 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_minishell/minishell.h"

bool	no_quotes(bool *quotes)
{
	return (quotes[0] == false && quotes[1] == false);
}

char	**realloc_tab(char ***prev, int size)
{
	char	**new;
	int		i;

	new = ft_calloc(sizeof(char *), size + 25);
	if (!new)
		return (ft_free_double_ptr(prev), NULL);
	i = -1;
	while(++i < size)
		new[i] = (*prev)[i];
	new[i] = NULL;
	free(*prev);
	return (new);
}

char	**get_all_files()
{
	char			pwd[MAX_PATH];
	DIR				*dir;
	struct dirent	*entry;
	char			**joined;
	int				i;
	int				tabsize;

	entry = NULL;
	dir = NULL;
	i = 0;
	tabsize = 25;
	joined = ft_calloc(sizeof(char *), tabsize);
	if (!joined)
		return (false);
	ft_bzero(pwd, MAX_PATH);
	if (getcwd(pwd, MAX_PATH) != pwd)
		return (NULL);
	dir = opendir(pwd);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (i == tabsize - 1)
		{
			joined = realloc_tab(&joined, tabsize);
			if (!joined)
				return (NULL);
			tabsize += 25;
		}
		if (entry->d_name[0] != '.')
		{
			joined[i] = ft_strdup(entry->d_name);
			if (!joined[i])
				return (ft_free_double_ptr(&joined), NULL);
			i++;
		}
		entry = readdir(dir);
	}
	joined[i] = NULL;
	closedir(dir);
	return (joined);
}

void	get_files(char **cmd, int *index)
{
	char	**files;
	char	*joined;
	char	*tmp;
	char	*final;
	char	*before;
	char	*after;
	int		i;

	if (!cmd || !*cmd || !index)
		return ;
	i = 0;
	joined = ft_strdup("");
	files = get_all_files();
	if (!files)
		return ((void)((*index)++));
	while (files[i])
	{
		tmp = joined;
		if (i == 0)
			joined = ft_str_three_join(joined, "", files[i]);
		else
			joined = ft_str_three_join(joined, " ", files[i]);
		free(tmp);
		i++;
	}
	before = ft_substr(*cmd, 0, *index);
	after =  ft_substr(*cmd, *index + 1, ft_strlen(&(*cmd)[*index + 1]));
	final = ft_str_three_join(before ,joined, after);
	free(*cmd);
	*cmd = final;
	free(joined);
	free(before);
	free(after);
	ft_free_double_ptr(&files);
}

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
	files = get_all_files();
	if (!files)
		return (free(pattern), NULL);
	validfiles = ft_calloc(sizeof(char *), tab_size(files) + 1);
	i = -1;
	j = 0;
	while (files[++i])
	{
		if (match_pattern(files[i], pattern))
		{
			validfiles[j] = ft_strdup(files[i]);
			j++;
		}
	}
	validfiles[j] = NULL;
	ft_free_double_ptr(&files);
	free(pattern);
	if (tab_size(validfiles) == 0)
		ft_free_double_ptr(&validfiles);
	return (validfiles);
}

char	**expand_wildcards(char	**cmd)
{
	bool	quotes[2]; // 0 : single, 1 : double
	int		i;
	int		start;
	int		end;
	char	**files;

	if (!*cmd || ft_count_char_in_str(*cmd, '*') == 0)
		return (NULL);
	clean_quotes(cmd);
	i = 0;
	start = 0;
	files = NULL;
	end = 0;
	quotes[0] = false;
	quotes[1] = false;
	while ((*cmd)[i])
	{
		if ((*cmd)[i] == '\"')
			quotes[1] = !quotes[1];
		if ((*cmd)[i] == '\'')
			quotes[0] = !quotes[0];
		if ((*cmd)[i] == '*' && no_quotes(quotes))
		{
			start = i;
			while (start > 0 && !ft_isspace((*cmd)[start - 1]))
				start--;
			end = i;
			while ((*cmd)[end] && !ft_isspace((*cmd)[end]))
				end++;
			// get_files
			if (end - start == 1)
				files = get_all_files();
			else
				files = search_for_matching_files(cmd, ft_substr(*cmd, start, end - start));
			i = end;
			break ;
		}
		i++;
	}
	return (files);
}

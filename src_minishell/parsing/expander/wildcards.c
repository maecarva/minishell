/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:41:09 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/17 18:00:37 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_minishell/minishell.h"

/*
struct dirent {
    ino_t          d_ino;       // numéro d'inœud 
    off_t          d_off;       // décalage jusqu'à la dirent suivante 
    unsigned short d_reclen;    // longueur de cet enregistrement 
    unsigned char  d_type;      // type du fichier 
    char           d_name[256]; // nom du fichier 
};
*/

bool	no_quotes(bool *quotes)
{
	return (quotes[0] == false && quotes[1] == false);
}

char	*get_all_files()
{
	char			pwd[MAX_PATH];
	DIR				*dir;
	struct dirent	*entry;
	char			*joined;
	char			*tmp;

	entry = NULL;
	dir = NULL;
	tmp = NULL;
	joined = ft_strdup("");
	if (!joined)
		return (false);
	ft_bzero(pwd, MAX_PATH);
	if (getcwd(pwd, MAX_PATH) != pwd)
		return (NULL);
	dir = opendir(pwd);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] != '.')
		{
			tmp = joined;
			joined = ft_strjoin(joined, entry->d_name);
			free(tmp);
			tmp = joined;
			joined = ft_strjoin(joined, " ");
			free(tmp);
		}
		entry = readdir(dir);
	}
	joined[ft_strlen(joined) - 1] = '\0';
	closedir(dir);
	return (joined);
}

char	*extract_valid_files(char **splited, char *before, char *after)
{
	int		i;
	bool	validbefore;
	bool	validafter;
	char	*valid_files;
	char	*tmp;

	if (!splited || !*splited || !before || !after)
		return (NULL);
	tmp = ft_strdup("");
	if (!tmp)
		return (NULL);
	i = 0;
	valid_files = NULL;
	while (splited[i])
	{
		validbefore = false;
		validafter = false;
		if (ft_strnstr(splited[i], before, ft_strlen(splited[i])) == splited[i])
			validbefore = true;
		if (ft_strlen(before) == 0)
			validbefore = true;
		if (ft_strncmp(&splited[i][ft_strlen(splited[i]) - ft_strlen(after)], after, ft_strlen(after)) == 0)
			validafter = true;
		if (ft_strlen(after) == 0)
			validafter = true;
		if (validbefore && validafter)
		{
			if (*tmp == '\0')
				valid_files = ft_strjoin(tmp, splited[i]);
			else
				valid_files = ft_str_three_join(tmp, " ", splited[i]);
			if (!valid_files)
				return (free(tmp), NULL);
			free(tmp);
			tmp = valid_files;
		}
		i++;
	}
	return (valid_files);
}

char	*search_for_files(char **s, int *index, char *files)
{
	char	**splited;
	char	*before;
	char	*after;
	char	*valid_files;
	int		i;

	if (!*s || !index || !files)
		return (NULL);
	i = *index;
	splited = ft_split(files, ' ');
	if (!splited)
		return (NULL);
	while (!ft_isspace((*s)[i]) && i > 0)
		i--;
	before = ft_substr(*s, i, *index);
	if (!before)
		return (ft_free_double_ptr(&splited), NULL);
	i = *index;
	while (!ft_isspace((*s)[i]) && (size_t)i < ft_strlen(*s))
		i++;
	after = ft_substr(*s, *index + 1, i);
	if (!after)
		return (ft_free_double_ptr(&splited), free(before), NULL);
	valid_files = extract_valid_files(splited, before, after);
	ft_free_double_ptr(&splited);
	free(before);
	free(after);
	return (valid_files);
}

void	get_files(char **s, int *index, int how_many)
{
	char	*files;
	char	*tmp;
	int		i;
	int		j;

	if (!*s || !index)
		return ;
	files = NULL;
	tmp = NULL;
	i = 0;
	j = 0;
	files = get_all_files();
	if (!files)
		return ;
	if (how_many == GETALLFILES)
	{
		*index += ft_strlen(files);
		free(*s);
		*s = files;
	}
	else 
	{
		tmp = search_for_files(s, index, files);
		free(files);
		if (tmp)
		{
			i = *index;
			while (!ft_isspace((*s)[i]))
			{
				(*s)[i] = '\0';
				if (i == 0)
					break ;
				i--;
			}
			j = *index;
			while (!ft_isspace((*s)[j]) && (size_t)j < ft_strlen(*s))
			{
				(*s)[j] = '\0';
				j++;
			}
			files = ft_str_three_join(*s, tmp, &(*s)[j]);
			free(tmp);
			free(*s);
			*s = files;
		}
	}
}


void	search_for_matching_files(char **cmd, int start, int end, char *pattern)
{
	char	**splited;
	int		i;
	int		j;
	char	**files;
	bool	valid;
	char	*validfiles = ft_strdup("");

	if (!cmd || !*cmd || !pattern)
		return ;
	splited = ft_split(*cmd, '*');
	files = ft_split(get_all_files(), ' ');
	if (!splited)
		return (free(pattern));
	if (!files)
		return (free(pattern), ft_free_double_ptr(&splited));
	i = 0;
	while (files[i])
	{
		j = 0;
		valid = true;
		if (tab_size(splited) <= 1 && *pattern == '*' && pattern[ft_strlen(pattern)] == '*')
		{
			if (ft_strnstr(files[i], splited[j], ft_strlen(files[i])) == NULL)
				valid = false;
		}
		else 
		{
			while (splited[j] && valid == true)
			{
				if (j == 0 && *pattern != '*')
				{
					if (ft_strnstr(files[i], splited[j], ft_strlen(files[i])) != files[i])
						valid = false;
				}
				else if (j == tab_size(splited) - 1 && pattern[ft_strlen(pattern) - 1] != '*')
				{
					if (ft_strncmp(splited[j], &files[i][ft_strlen(files[i]) - ft_strlen(splited[j])], ft_strlen(splited[j])) != 0)
						valid = false;
				}
				else if (ft_strnstr(files[i], splited[j], ft_strlen(files[i])) != NULL)
				{
					if (splited[j + 1] == NULL)
						break ;
					if (ft_strnstr(files[i], splited[j + 1], ft_strlen(files[i])) != NULL)
					{
						if (ft_strnstr(files[i], splited[j], ft_strlen(files[i])) && ft_strnstr(files[i], splited[j + 1], ft_strlen(files[i])))
							valid = true;
					}
				}
				else {
					valid = false;
				}
				j++;
			}
			if (valid)
			{
				if (files[i + 1] == NULL || *validfiles == '\0')
					validfiles = ft_strjoin(validfiles, files[i]);
				else
					validfiles = ft_str_three_join(validfiles, " ", files[i]);
			}
			i++;
		}
	}
	if (ft_strlen(validfiles) > 0)
	{
		char *before = ft_substr(*cmd, 0, start);
		char *after = ft_substr(*cmd, end, ft_strlen(&(*cmd)[end]));
		free(*cmd);
		*cmd = ft_str_three_join(before, validfiles, after);
	}
	ft_free_double_ptr(&splited);
	ft_free_double_ptr(&files);
	free(pattern);
}

// todo : echo *** OK
// echo *l* search in middle
// echo Ma*invalidsearch OK
void	expand_wildcards(char	**cmd)
{
	bool	quotes[2]; // 0 : single, 1 : double
	int		i;
	int		start;
	int		end;

	if (!*cmd || ft_count_char_in_str(*cmd, '*') == 0)
		return ;
	i = 0;
	start = 0;
	end = 0;
	quotes[0] = false;
	quotes[1] = false;
	while ((*cmd)[i])
	{
		if ((*cmd)[i] == '\"')
			quotes[1] = !quotes[1];
		if ((*cmd)[i] == '\'')
			quotes[0] = !quotes[0];
		if ((*cmd)[i] == '*' && no_quotes(quotes) == true)
		{
			if ((*cmd)[i + 1] == '*')
				while ((*cmd)[i + 1] == '*')
					ft_strlcpy(&(*cmd)[i + 1], &(*cmd)[i + 2], ft_strlen(&(*cmd)[i + 1]));
			start = i;
			while (start > 0 && !ft_isspace((*cmd)[start - 1]))
				start--;
			end = i;
			while ((*cmd)[end] && !ft_isspace((*cmd)[end]))
				end++;
			// get_files
			if (end - start == 1)
				get_files(cmd, &i, GETALLFILES);
			else
				search_for_matching_files(cmd, start, end, ft_substr(*cmd, start, end - start));
			i += end;
		}
		i++;
	}
}

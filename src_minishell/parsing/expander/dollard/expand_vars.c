/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:19:34 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/26 18:47:39 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include_minishell/minishell.h"

int	expand_last_error(char **str, t_config *config, int *index)
{
	char	*ptrs[4];
	char	*s;
	int		j;

	j = *index + 1;
	s = *str;
	ft_bzero(ptrs, sizeof(char *) * 4);
	ptrs[1] = ft_itoa(config->last_error_code);
	ptrs[2] = ft_substr(s, 0, *index);
	ptrs[3] = ft_substr(s, j + 1, ft_strlen(s));
	ptrs[0] = ft_str_three_join(ptrs[2], ptrs[1], ptrs[3]);
	*index += ft_strlen(ptrs[1]) - 1;
	free(*str);
	free_array(ptrs, 4, 0);
	*str = ptrs[0];
	return (0);
}

int	expand_pid(char **str, t_config *config, int *index)
{
	char	*ptrs[4];
	char	*s;
	int		j;

	j = *index + 1;
	s = *str;
	ft_bzero(ptrs, sizeof(char *) * 4);
	ptrs[2] = ft_substr(s, 0, *index);
	ptrs[3] = ft_substr(s, j + 1, ft_strlen(s));
	ptrs[0] = ft_str_three_join(ptrs[2], config->pidstr, ptrs[3]);
	*index += ft_strlen(ptrs[1]) - 1;
	free(*str);
	free(ptrs[2]);
	free(ptrs[3]);
	*str = ptrs[0];
	return (0);
}

int	expand_classic2(char **ptrs, char **str, int j, int *index)
{
	char	*s;

	s = *str;
	ptrs[2] = ft_substr(s, 0, *index);
	ptrs[3] = ft_substr(s, j + 1, ft_strlen(s));
	ptrs[0] = ft_str_three_join(ptrs[2], ptrs[1], ptrs[3]);
	*index += ft_strlen(ptrs[1]) - 1;
	free_array(ptrs, 4, 0);
	free(*str);
	*str = ptrs[0];
	return (0);
}

int	expand_classic(char **str, t_config *config,
			int *index, bool expand_specials)
{
	char	*ptrs[4];
	char	*s;
	int		j;

	j = *index + 1;
	s = *str;
	ft_bzero(ptrs, sizeof(char *) * 4);
	while (s[j] && ((ft_isalnum(s[j]) || s[j] == '_')
			&& (ft_isalnum(s[j + 1]) || s[j + 1] == '_')) && s[j + 1] != '/')
		j++;
	ptrs[0] = ft_substr(s, *index + 1, j - *index);
	if (!ptrs[0])
		return (0);
	ptrs[1] = get_value_by_name(config->environnement, ptrs[0]);
	free(ptrs[0]);
	if (!ptrs[1])
		ft_memmove(&s[*index], &s[j + 1], ft_strlen(&s[j]));
	else if (expand_specials == false && is_special_var(ptrs[1]))
	{
		*index += ft_strlen(ptrs[1]);
		return (free_array(ptrs, 4, 0), 1);
	}
	else
		return (expand_classic2(ptrs, str, j, index));
	return (0);
}

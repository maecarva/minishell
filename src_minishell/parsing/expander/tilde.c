/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:00:41 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/25 11:02:59 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_minishell/minishell.h"

void	expand_tilde_pls(char **s, char *home, int index)
{
	char	*before;
	char	*after;
	char	*final;

	if (!s || !*s || !home)
		return ;
	before = ft_substr(*s, 0, index);
	after = ft_substr(*s, index + 1, ft_strlen(&(*s)[index]));
	final = NULL;
	if (!after || !before)
		return (free(after), free(before));
	final = ft_str_three_join(before, home, after);
	if (!final)
		return (free(after), free(before));
	free(*s);
	*s = final;
}

void	expand_tilde(char **s, t_config *minishell)
{
	bool	dq;
	bool	sq;
	char	*home;
	int		i;

	if (!s || !*s || !minishell)
		return ;
	home = get_value_by_name(minishell->environnement, "HOME");
	if (!home)
		return ;
	i = 0;
	sq = false;
	dq = false;
	
	while ((*s)[i])
	{
		if ((*s)[i] == '\'')
			sq = !sq;
		else if ((*s)[i] == '\"')
			dq = !dq;
		if (sq == false && dq == false && (*s)[i] == '~' && (ft_isspace((*s)[i + 1]) || (*s)[i + 1] == '\0'))
			expand_tilde_pls(s, home, i);
		i++;
	}
	free(home);
}

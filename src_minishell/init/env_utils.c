/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:38:45 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/03 14:39:30 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

t_envvar	*ptr_to_envvar(void	*content)
{
	if (!content)
		return (NULL);
	return ((t_envvar *)content);
}

char	*get_value_by_name(t_list *env, char *name)
{
	t_list		*tmp;
	t_envvar	*tmpvar;

	tmp = env;
	while (tmp)
	{
		tmpvar = ptr_to_envvar(tmp->content);
		if (ft_strncmp(name, tmpvar->name, ft_strlen(name)) == 0)
			return (tmpvar->value);
		tmp = tmp->next;
	}
	return (NULL);
}

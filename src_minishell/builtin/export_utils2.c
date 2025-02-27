/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:37:44 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/27 13:43:40 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_export(char *str1, char *str2, char *str3, t_config *ms_data)
{
	perror("malloc");
	ft_free_simple_ptr(&str1);
	ft_free_simple_ptr(&str2);
	ft_free_simple_ptr(&str3);
	ms_data->last_error_code = ERROR_CODE;
	clear_minishell(ms_data);
}

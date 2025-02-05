/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:16:52 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/05 11:39:08 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*get_dollar_variable(char *argument, int *actual_i)
// {
// 	char	*variable;
// 	int	i;

// 	i = 0;
// 	while (ft_isalnum(argument[i]) == 1 || argument[i] == '_')
// 		i++;
// 	variable = malloc(sizeof(char) * (i + 1));
// 	if (!variable)
// 		return (NULL);
// 	*actual_i += i;
// 	ft_strlcpy(variable, argument, i + 1);
// 	return (variable);
// }

// static void	deal_with_dollar(char *variable, char **envp)
// {
// 	int	i;
// 	int	j;
// 	int	n;
// 	int	len_var;

// 	i = 0;
// 	while (envp[i])
// 	{
// 		j = 0;
// 		while (envp[i][j] && envp[i][j] != '=')
// 			j++;
// 		len_var = ft_strlen(variable);
// 		n = ft_max(len_var, j);
// 		if (ft_strncmp(variable, envp[i], n) == 0)
// 		{
// 			printf("%s", envp[i] + j + 1);
// 			return ;
// 		}
// 		i++;
// 	}
// }

void	echo(t_btree *tree, char **envp)
{
	// int		i;
	// char	*variable;
	perror("hey");
	perror(envp[1]);
	(void )tree;
/*
	while (command.arguments != NULL)
	{
		i = 0;
		while (((char *)command.arguments->content)[i])
		{
			if (command.quotes == true && ((char *)command.arguments->content)[i] == '$')
			{
				i++;
				variable = get_dollar_variable(&((char *)command.arguments->content)[i], &i);
				if (!variable)
					ft_perror("malloc", ERROR_CODE);
				deal_with_dollar(variable, envp);
				free(variable);
			}
			else
			{
				printf("%c", ((char *)command.arguments->content)[i]);
				i++;
			}
		}
		command.arguments = command.arguments->next;
		if (command.arguments != NULL)
			printf(" ");
	}
	if (command.flags == 0)
		printf("\n");
*/
}

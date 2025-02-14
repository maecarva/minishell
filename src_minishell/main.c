/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:05:52 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/13 21:31:14 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_minishell/minishell.h"

	// char		*cmd = "<infile << limiter wc -c > outfile >> appendfile";
	// char		*cmd = "ls -la | wc -c | grep README.md > outfile.txt";
	// char		*cmd = "<Makefile cat| echo \"$PWD '\"hola\"'\" ~/src | 'tr' -d / >outfile";

int	main(int ac, char **av, char **env)
{
	t_config	*minishell;
	char	*cmd;
	t_btree	*ast;

	minishell = init(ac, av, env);
	if (!minishell)
		return (1);
	while (1)
	{
		cmd = readline(minishell->prompt);
		if (!cmd)
			return (printf("exit\n"), clear_minishell(minishell));
		add_history(cmd);
		if (cmd[0] != '\0')
		{
			ast = parse_cmd2(cmd, minishell);
			minishell->ast = ast;
			if (!minishell->ast)
			{
				free(cmd);
				continue ;
			}
			// print_arbre(minishell->ast, 0);
			free(cmd);
			check_type_execute(minishell);
			free_ast(&ast);
		}
	}
	return (clear_minishell(minishell));
}

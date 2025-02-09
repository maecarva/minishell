/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:05:52 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/08 17:07:30 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_minishell/minishell.h"

void	print_env(t_config *minishell)
{
	int	i;

	i = 0;
	while (minishell->environnement[i])
	{
		printf("%s\n", minishell->environnement[i]);
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	t_config	*minishell;
	// char		*cmd = "<infile << limiter wc -c > outfile >> appendfile";
	// char		*cmd = "ls -la | wc -c | grep README.md > outfile.txt";
	// char		*cmd = "<Makefile cat| echo \"$PWD '\"hola\"'\" ~/src | 'tr' -d / >outfile";
	char	*cmd;
	t_btree		*ast;

	// init_signals();
	minishell = init(ac, av, env);
	if (!minishell)
		return (1);


	// t_pipes	p_data;

	// init_p_data(&p_data, arbrebidon, env);
	// pipes(&p_data);

	
	while (1)
	{
		cmd = readline(minishell->prompt);
		if (!cmd)
			return (printf("exit\n"), clear_minishell(minishell), 1);

		add_history(cmd);
		// if (cmd[0] != '\0')
		// {
		// 	ast = parse_cmd(cmd);
		// 	check_type_execute(ast, env);
		// 	clear_ast(ast);
		// }

	ast = parse_cmd2(cmd, minishell);
	if (!ast)
	{
		free(cmd);
		continue ;
	}
		// init_p_data(&p_data, ast, env);
	// print_arbre(ast, 0);
		// pipes(ast, env);
	// clear_ast(ast);
	free(cmd);
	}
	clear_minishell(minishell);
	return (EXIT_SUCCESS);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:05:52 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/09 19:34:55 by maecarva         ###   ########.fr       */
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
	t_btree	*ast;

	// init_signals();
	minishell = init(ac, av, env);
	if (!minishell)
		return (1);
	while (1)
	{
		cmd = readline(minishell->prompt);
		if (!cmd)
			return (printf("exit\n"), clear_minishell(minishell), 1);
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
			check_type_execute(minishell);
			free_ast(&ast);
			free(cmd);
		}
	}
	return (clear_minishell(minishell));
}


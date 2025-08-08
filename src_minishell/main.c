/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:05:52 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/26 22:35:51 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_minishell/minishell.h"

	// char		*cmd = "<infile << limiter wc -c > outfile >> appendfile";
	// char		*cmd = "ls -la | wc -c | grep README.md > outfile.txt";
	// char		*cmd = "<Makefile cat| echo \"$PWD '\"hola\"'\" ~/src | 'tr' -d / >outfile";

int	last_signal_received;

int	main(int ac, char **av, char **env)
{
	t_config	*minishell;
	char	*cmd;
	t_btree	*ast;

	minishell = init(ac, av, env);
	if (!minishell)
		return (1);
	if (ac == 3 && ft_strcmp(av[1], "-c") == 0 && av[2])
	{
		int i;
		char **arg_input;
		arg_input = ft_split(av[2], ';');
		if (!arg_input)
			return (clear_minishell(minishell));
		i = 0;
		while (arg_input[i])
		{
			ast = parse_cmd(arg_input[i], minishell);
			minishell->ast = ast;
			if (!minishell->ast)
			{
				i++;
				continue ;
			}
			
			minishell->dont_fucking_touch_me = ast;
			execute_ast(minishell->ast, minishell);
			free_ast(&(minishell->dont_fucking_touch_me));
			i++;
		}
	}
	else {
	
		while (1)
		{
			if (isatty(fileno(stdin)))
				cmd = readline(minishell->prompt);
			else
			{
				char *line = NULL;
				get_next_line(fileno(stdin), &line);
				if (line == NULL)
					break ;
				cmd = ft_strtrim(line, "\n");
				free(line);
			}
			if (!cmd)
				return (printf("exit\n"), clear_minishell(minishell));
			refresh_signal(minishell);
			add_history(cmd);
			if (cmd[0] != '\0')
			{
				ast = parse_cmd(cmd, minishell);
				minishell->ast = ast;
				if (!minishell->ast)
				{
					free(cmd);
					continue ;
				}
				minishell->dont_fucking_touch_me = ast;
				free(cmd);
				get_here_docs(minishell);
                execute_ast(minishell->ast, minishell);
				clear_here_doc(minishell->ast);
				minishell->ast = minishell->dont_fucking_touch_me;
				free_ast(&(minishell->dont_fucking_touch_me));
			}
		}
	}
	return (clear_minishell(minishell));
}

// raouter clear all hd dans clear minishell

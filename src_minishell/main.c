/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:05:52 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/04 16:22:01 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_minishell/minishell.h"

void	print_env(t_config *minishell)
{

	t_list		*tmp;

	tmp = minishell->environnement;
	while (tmp)
	{
		printf("%s=%s\n", ((t_envvar *)tmp->content)->name, ((t_envvar *)tmp->content)->value);
		tmp = tmp->next;
	}
}

int	main(int ac, char **av, char **env)
{
	t_config	*minishell;
	char		*cmd;
	t_btree		*ast;

	init_signals();
	minishell = init(ac, av, env);
	if (!minishell)
		return (1);
	// t_btree	*arbrebidon = arbre_bidon();
	// printf("mid=%s\n", (char *)arbrebidon->item);
	// printf("left=%s\n", (char *)arbrebidon->left->item);

	t_pipes	p_data;

	// init_p_data(&p_data, arbrebidon, env);
	// pipes(&p_data);
	
	while (1)
	{
		cmd = readline(minishell->prompt);
		if (!cmd)
			return (printf("exit\n"), clear_minishell(minishell), 1);
		ast = parse_cmd(cmd);
		init_p_data(&p_data, ast, env);
		pipes(&p_data);
		clear_ast(ast);
		free(cmd);
	}
	clear_minishell(minishell);
	return (0);
}

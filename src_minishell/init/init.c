/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:38:51 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/13 20:52:36 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

char	*get_minishell_pid()
{
	int		fd;
	char	*fline;
	char	*pid;
	int		i;

	i = 0;
	pid = NULL;
	fline = NULL;
	fd = open("/proc/self/stat", O_RDONLY);
	if (fd == -1)
		return (NULL);
	if (get_next_line(fd, &fline) != 0)
	{
		if (fline != NULL)
			free(fline);
		return (NULL);
	}
	while (fline[i] && ft_isdigit(fline[i]))
		i++;
	pid = ft_substr(fline, 0, i);
	free(fline);
	return (pid);
}

int	init_config(int ac, char **av, t_config *minishell)
{
	char	*tmp;
	minishell->ac = ac;
	minishell->av = av;
	minishell->current_path = get_value_by_name(minishell->environnement, "PWD");
	if (minishell->current_path == NULL)
		return (INIT_ERROR);
	tmp = get_value_by_name(minishell->environnement, "LOGNAME");
	if (!tmp)
		return (INIT_ERROR);
	minishell->prompt = ft_strjoin(tmp, " ~> \x1B[32mminishell #\x1B[37m ");
	free(tmp);
	if (minishell->prompt == NULL)
		return (INIT_ERROR);
	minishell->pidstr = get_minishell_pid();
	return (INIT_OK);
}

char	**init_no_env()
{
	char	**env;
	char	pwd[MAX_PATH];

	ft_bzero(pwd, MAX_PATH);
	getcwd(pwd, MAX_PATH);
	env = ft_calloc(NO_ENV_DEFAULT_SIZE + 1, sizeof(char *));
	if (!env || *pwd == '\0')
		return (NULL);
	env[0] = ft_strdup("PATH=/usr/local/sbin:/usr/local/bin:/usr/bin");
	env[1] = ft_strjoin("PWD=", pwd);
	env[2] = ft_strdup("SHLVL=1");
	env[3] = ft_strdup("_=/usr/bin/env");
	env[4] = ft_strdup("TERM=xterm-256color");
	env[5] = ft_strdup("LOGNAME=👻 (unknown)");
	env[NO_ENV_DEFAULT_SIZE] = NULL;
	return (env);
}

t_config	*init(int ac, char **av, char **env)
{
	t_config	*minishell;

	if (isatty(STDIN_FILENO) == 0 ||isatty(STDOUT_FILENO) == 0 || isatty(STDERR_FILENO) == 0)
		return (NULL);
	minishell = ft_calloc(sizeof(t_config), 1);
	if (!minishell)
		return (NULL);
	if (!env || !*env)
		minishell->environnement = init_no_env();
	else
		minishell->environnement = init_environnement(env);
	if (!minishell->environnement)
		return (clear_minishell(minishell), NULL);
	if (init_config(ac, av,minishell) == INIT_ERROR)
		return (clear_minishell(minishell), NULL);
	signals_interactive_mode();
	return (minishell);
}

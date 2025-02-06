/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:00:24 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/06 13:26:45 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_input(t_minishell *ms_data)
{
	int	fd;

	fd = open(((t_node *)ms_data->tree->item)->cmd->cmd, O_RDONLY, 0644);
	if (fd == -1)
		ft_perror("open", ERROR_CODE);
	ms_data->name_infile = ((t_node *)ms_data->tree->item)->cmd->cmd;
	close(fd);
}

void	get_output(t_minishell *ms_data)
{
	int	fd;

	fd = open(((t_node *)ms_data->tree->item)->cmd->cmd, O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		ft_perror("open", ERROR_CODE);
	ms_data->name_outfile = ((t_node *)ms_data->tree->item)->cmd->cmd;
	close(fd);
}

void	get_output_here_doc(t_minishell *ms_data)
{
	int	fd;

	fd = open(((t_node *)ms_data->tree->item)->cmd->cmd, O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		ft_perror("open", ERROR_CODE);
	ms_data->name_outfile = ((t_node *)ms_data->tree->item)->cmd->cmd;
	close(fd);
}

void	get_input_here_doc(t_minishell *ms_data)
{
	int		fd;
	char	*line;

	fd = open(((t_node *)ms_data->tree->item)->cmd->cmd, O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		ft_perror("open", ERROR_CODE);
	// while (1)
	// {
	// 	if (get_next_line(0, &line) == ERROR_CODE)
	// 		ft_perror("malloc", ERROR_CODE);
	// 	if (ft_strcmp(line, ((t_node *)ms_data->tree->item)->cmd->cmd) == '\n')
	// 		break;
	// 	ft_putstr_fd(line, ((t_node *)ms_data->tree->item)->cmd->cmd);       // faire gaffe, ptet que faut rajouter /n a la fin
	// }
	ms_data->name_outfile = ((t_node *)ms_data->tree->item)->cmd->cmd;
	close(fd);
}

void	find_redirection(t_minishell *ms_data)
{
	if (!ms_data->tree)
		return ;
	while (ms_data->tree)
	{
		if (((t_node *)ms_data->tree->item)->type == R_LEFT)
			get_input(ms_data);
		else if (((t_node *)ms_data->tree->item)->type == R_RIGHT)
			get_output(ms_data);
		else if (((t_node *)ms_data->tree->item)->type == RR_LEFT)
			get_input_here_doc(ms_data);
		else if (((t_node *)ms_data->tree->item)->type == RR_RIGHT)
			get_output_here_doc(ms_data);
		ms_data->tree = ms_data->tree->right;
	}
}

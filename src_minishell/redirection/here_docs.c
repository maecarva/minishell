/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:40:51 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/21 17:18:13 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_hd(t_list **list_hd, char *limiter)
{
	char	*line;
	char	*name_here_doc;

	name_here_doc = get_random_name_here_doc;
	p_data->fd_infile = open("here_doc.tmp", O_WRONLY | O_CREAT, 0644);
	if (p_data->fd_infile == -1)
	{
		perror("here_doc.tmp");
		ft_close(&p_data->to_close_one);
		ft_close(&p_data->to_close_two);
		free_fd(&(p_data->fd), p_data->nb_pipes);
		p_data->ms_data->last_error_code = ERROR_CODE;
		clear_minishell(p_data->ms_data);
	}
	p_data->is_hd = true;
	line = NULL;
	while (1)
	{
		if (get_next_line(0, &line) == -1)
		{
			perror("malloc");
			unlink_hd(p_data);
			ft_close(&p_data->to_close_one);
			ft_close(&p_data->to_close_two);
			free_fd(&(p_data->fd), p_data->nb_pipes);
			p_data->ms_data->last_error_code = ERROR_CODE;
			clear_minishell(p_data->ms_data);
		}
		if (ft_strncmp(line, limiter,
				ft_max(ft_strlen(limiter), ft_strlen(line))) == '\n')
		{
			free(line);
			ft_close(&p_data->fd_infile);
			return ;
		}
		ft_putstr_fd(line, p_data->fd_infile);
	}
}

t_list	*get_here_docs(t_config *ms_data)
{
	t_list	*hd;

	ft_btree_apply_infix(t_btree *root, void fill_t_list);
	return (hd);
}

void	fill_list_hd(t_btree *actual_cmd)
{
	t_btree	*cmd;

	cmd = actual_cmd;
	while (cmd->left)
	{
		cmd = cmd->left;
		if (((t_node2 *)(cmd->item))->type == HEREDOC)
			
	}
}

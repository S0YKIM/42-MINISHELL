/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 00:52:42 by heehkim           #+#    #+#             */
/*   Updated: 2022/05/03 23:30:20 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_heredoc(t_ast *ast)
{
	if (!ast || ast->type < T_RDR)
		return ;
	if (ast->type == T_RDR && ast->fd != -1)
		close_fd(ast->fd);
	close_heredoc(ast->left);
	close_heredoc(ast->right);
}

void	close_parent_fds(t_data *data, int i)
{
	if (i <= 0)
		return ;
	close_fd(data->pl_list[i - 1]->pipe_fd[READ]);
	close_fd(data->pl_list[i - 1]->pipe_fd[WRITE]);
	close_heredoc(data->pl_list[i - 1]);
}

void	close_child_fds(int in_fd, int out_fd, t_ast *curr, t_ast *prev)
{
	if (in_fd != STDIN_FILENO)
		close_fd(in_fd);
	if (out_fd != STDOUT_FILENO)
		close_fd(out_fd);
	close_fd(curr->pipe_fd[READ]);
	close_fd(curr->pipe_fd[WRITE]);
	if (prev)
	{
		close_fd(prev->pipe_fd[READ]);
		close_fd(prev->pipe_fd[WRITE]);
	}
}

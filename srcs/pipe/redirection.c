/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 20:16:10 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/22 22:39:57 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_in_fd(t_ast *ast, int *in_fd)
{
	int	fd;

	fd = ast->fd;
	if (fd == -1)
		fd = open_infile(ast->left->token);
	if (*in_fd != STDIN_FILENO)
		close_fd(*in_fd);
	*in_fd = fd;
}

static void	set_out_fd(t_ast *ast, int *out_fd)
{
	int	fd;
	int	flag;

	flag = O_WRONLY | O_CREAT | O_TRUNC;
	if (ft_strlen(ast->token) == 2)
		flag = O_WRONLY | O_CREAT | O_APPEND;
	fd = open_outfile(ast->left->token, flag);
	if (*out_fd != STDOUT_FILENO)
		close_fd(*out_fd);
	*out_fd = fd;
}

void	traverse_redirection(t_ast *ast, int *in_fd, int *out_fd)
{
	if (!ast || ast->type != T_RDR)
		return ;
	if (*ast->token == '<')
		set_in_fd(ast, in_fd);
	else
		set_out_fd(ast, out_fd);
	traverse_redirection(ast->right, in_fd, out_fd);
}

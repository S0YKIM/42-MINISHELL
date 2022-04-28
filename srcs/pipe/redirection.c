/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 20:16:10 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/27 01:30:46 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_in_fd(t_ast *ast, int *in_fd)
{
	int	fd;

	fd = ast->fd;
	if (fd == -1)
	{
		fd = open_infile(ast->left->token);
		if (fd == ERROR)
			return (FALSE);
	}
	if (*in_fd != STDIN_FILENO)
	{
		if (close_fd(*in_fd) == ERROR)
			return (FALSE);
	}
	*in_fd = fd;
	return (TRUE);
}

static int	set_out_fd(t_ast *ast, int *out_fd)
{
	int	fd;
	int	flag;

	flag = O_WRONLY | O_CREAT | O_TRUNC;
	if (ft_strlen(ast->token) == 2)
		flag = O_WRONLY | O_CREAT | O_APPEND;
	fd = open_outfile(ast->left->token, flag);
	if (fd == ERROR)
		return (FALSE);
	if (*out_fd != STDOUT_FILENO)
	{
		if (close_fd(*out_fd) == ERROR)
			return (FALSE);
	}
	*out_fd = fd;
	return (TRUE);
}

int	traverse_redirection(t_ast *ast, int *in_fd, int *out_fd)
{
	if (!ast || ast->type != T_RDR)
		return (TRUE);
	if (*ast->token == '<')
	{
		if (!set_in_fd(ast, in_fd))
			return (FALSE);
	}
	else
		if (!set_out_fd(ast, out_fd))
			return (FALSE);
	return (traverse_redirection(ast->right, in_fd, out_fd));
}

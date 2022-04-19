/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 20:16:10 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/19 22:15:33 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_file_error(char *path)
{
	ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	return (FALSE);
}

static int	set_in_fd(t_ast *ast, int *in_fd)
{
	int	fd;

	fd = ast->fd;
	if (fd == -1)
	{
		fd = open(ast->left->token, O_RDONLY);
		if (fd == ERROR)
			return (print_file_error(ast->left->token));
	}
	if (*in_fd != STDIN_FILENO)
	{
		if (close(*in_fd) == ERROR)
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
	fd = open(ast->left->token, flag, 0644);
	if (fd == ERROR)
		return (print_file_error(ast->left->token));
	if (*out_fd != STDOUT_FILENO)
	{
		if (close(*out_fd) == ERROR)
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
	{
		if (!set_out_fd(ast, out_fd))
			return (FALSE);
	}
	if (!traverse_redirection(ast->right, in_fd, out_fd))
		return (FALSE);
	return (TRUE);
}

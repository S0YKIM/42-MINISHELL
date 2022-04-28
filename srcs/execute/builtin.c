/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 01:00:46 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/28 20:00:19 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_ast *ast, t_data *data)
{
	int	ret;

	ret = SUCCESS;
	if (!ft_strcmp(ast->argv[0], "cd"))
		ret = ft_cd(ast);
	else if (!ft_strcmp(ast->argv[0], "echo"))
		ret = ft_echo(ast);
	else if (!ft_strcmp(ast->argv[0], "env"))
		ret = ft_env(ast);
	else if (!ft_strcmp(ast->argv[0], "exit"))
		ft_exit(ast, data);
	else if (!ft_strcmp(ast->argv[0], "export"))
		ret = ft_export(ast);
	else if (!ft_strcmp(ast->argv[0], "pwd"))
		ret = ft_pwd();
	else if (!ft_strcmp(ast->argv[0], "unset"))
		ret = ft_unset(ast);
	else
		return (FALSE);
	update_env("?", ft_itoa(ret));
	return (TRUE);
}

static void	reset_fds(int stdin_fd, int stdout_fd)
{
	dup_fd(stdin_fd, STDIN_FILENO);
	dup_fd(stdout_fd, STDOUT_FILENO);
	close_fd(stdin_fd);
	close_fd(stdout_fd);
}

int	execute_one_builtin(t_data *data)
{
	int	stdin_fd;
	int	stdout_fd;
	int	in_fd;
	int	out_fd;

	in_fd = STDIN_FILENO;
	out_fd = STDOUT_FILENO;
	stdin_fd = dup(STDIN_FILENO);
	stdout_fd = dup(STDOUT_FILENO);
	if (!traverse_redirection(data->pl_list[0]->left, &in_fd, &out_fd))
		return (FALSE);
	if (in_fd != STDIN_FILENO)
	{
		dup_fd(in_fd, STDIN_FILENO);
		close_fd(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		dup_fd(out_fd, STDOUT_FILENO);
		close_fd(out_fd);
	}
	exec_builtin(data->pl_list[0]->right, data);
	reset_fds(stdin_fd, stdout_fd);
	return (TRUE);
}

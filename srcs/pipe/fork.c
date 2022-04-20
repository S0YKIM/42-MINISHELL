/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:19:46 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/20 16:35:22 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child(t_ast *ast)
{
	int	in_fd;
	int	out_fd;

	in_fd = STDIN_FILENO;
	out_fd = STDOUT_FILENO;
	if (!traverse_redirection(ast->left, &in_fd, &out_fd))
		exit(EXIT_FAILURE);
	printf("in_fd: %d | out_fd: %d\n", in_fd, out_fd);
}

int	traverse_fork(t_data *data, t_ast *ast)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (!ast || ast->type < T_PL)
		return (TRUE);
	if (ast->type == T_PL)
	{
		if (pipe(fd) == ERROR)
			return (FALSE);
		pid = fork();
		if (pid == ERROR)
			return (FALSE);
		else if (pid == 0)
			child(ast);
		else
		{
			if (waitpid(pid, &status, 0) == ERROR)
				return (FALSE);
		}
	}
	if (!traverse_fork(data, ast->left))
		return (FALSE);
	return (traverse_fork(data, ast->right));
}

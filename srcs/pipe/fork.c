/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:19:46 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/19 18:28:39 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	traverse_fork(t_ast *ast)
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
		{
			// 자식 프로세스
		}
		else
		{
			if (waitpid(pid, &status, 0) == ERROR)
				return (FALSE);
		}
	}
	if (!traverse_fork(ast->left))
		return (FALSE);
	if (!traverse_fork(ast->right))
		return (FALSE);
	return (TRUE);
}

int	fork_process(t_data *data)
{
	if (!traverse_fork(data->astree))
		return (FALSE);
	return (TRUE);
}

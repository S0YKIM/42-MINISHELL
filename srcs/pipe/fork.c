/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:19:46 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/25 18:36:20 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_child_fds(int in_fd, int out_fd, t_ast *curr, t_ast *prev)
{
	if (in_fd != STDIN_FILENO)
		close_fd(in_fd);
	if (out_fd != STDOUT_FILENO)
		close_fd(out_fd);
	close_fd(curr->pipe_fd[WRITE]);
	if (prev)
	{
		close_fd(prev->pipe_fd[READ]);
		close_fd(prev->pipe_fd[WRITE]);
	}
}

static void	child(t_data *data, int i)
{
	t_ast	*curr;
	t_ast	*prev;
	int		in_fd;
	int		out_fd;

	curr = data->pl_list[i];
	prev = NULL;
	if (i != data->pl_cnt - 1)
		prev = data->pl_list[i + 1];
	in_fd = STDIN_FILENO;
	out_fd = STDOUT_FILENO;
	traverse_redirection(curr->left, &in_fd, &out_fd);
	if (in_fd != STDIN_FILENO)
		dup_fd(in_fd, STDIN_FILENO);
	else if (i != data->pl_cnt - 1)
		dup_fd(prev->pipe_fd[READ], STDIN_FILENO);
	if (out_fd != STDOUT_FILENO)
		dup_fd(out_fd, STDOUT_FILENO);
	else if (i != 0)
		dup_fd(curr->pipe_fd[WRITE], STDOUT_FILENO);
	close_child_fds(in_fd, out_fd, curr, prev);
	set_signal();
	execute_cmd(curr->right, data);
}

static int	parent(int pid)
{
	int	status;

	set_signal();
	if (waitpid(pid, &status, 0) == ERROR)
		return (FALSE);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	update_env("?", ft_itoa(status));
	return (TRUE);
}

int	fork_process(t_data *data)
{
	pid_t	pid;
	int		i;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (data->curr_pl >= data->pl_cnt)
		return (TRUE);
	i = (data->curr_pl)++;
	if (pipe(data->pl_list[i]->pipe_fd) == ERROR)
		return (FALSE);
	pid = fork();
	if (pid == ERROR)
		return (FALSE);
	else if (pid == 0)
	{
		if (!fork_process(data))
			return (FALSE);
		child(data, i);
	}
	return (parent(pid));
}

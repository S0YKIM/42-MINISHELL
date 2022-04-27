/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:19:46 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/27 16:41:01 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child(t_data *data, int i)
{
	t_ast	*curr;
	t_ast	*prev;
	int		in_fd;
	int		out_fd;

	curr = data->pl_list[i];
	prev = NULL;
	if (i != 0)
		prev = data->pl_list[i - 1];
	in_fd = STDIN_FILENO;
	out_fd = STDOUT_FILENO;
	if (!traverse_redirection(curr->left, &in_fd, &out_fd))
		exit(EXIT_FAILURE);
	if (in_fd != STDIN_FILENO)
		dup_fd(in_fd, STDIN_FILENO);
	else if (i != 0)
		dup_fd(prev->pipe_fd[READ], STDIN_FILENO);
	if (out_fd != STDOUT_FILENO)
		dup_fd(out_fd, STDOUT_FILENO);
	else if (i != data->pl_cnt - 1)
		dup_fd(curr->pipe_fd[WRITE], STDOUT_FILENO);
	close_child_fds(in_fd, out_fd, curr, prev);
	if (!curr->right)
		exit(EXIT_SUCCESS);
	execute_cmd(curr->right, data);
}

static int	parent(t_data *data, int i)
{
	close_parent_fds(data, i);
	if (!ft_strcmp("./minishell", data->token_list->data))
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	set_signal();
	return (TRUE);
}

static int	wait_pids(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->pl_cnt)
	{
		if (waitpid(data->pids[i], &status, 0) == ERROR)
			return (FALSE);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		i++;
	}
	if (!update_env("?", ft_itoa(status)))
		return (FALSE);
	return (TRUE);
}

int	fork_process(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->pl_cnt)
	{
		if (pipe(data->pl_list[i]->pipe_fd) == ERROR)
			return (FALSE);
		data->pids[i] = fork();
		if (data->pids[i] == ERROR)
			return (FALSE);
		else if (data->pids[i] == 0)
			child(data, i);
		else
		{
			if (!parent(data, i))
				return (FALSE);
		}
		i++;
	}
	close_parent_fds(data, i);
	return (wait_pids(data));
}

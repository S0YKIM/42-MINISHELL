/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:02:56 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/25 18:23:54 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 나중에 지우기
void	read_fd(int fd)
{
	int		n;
	char	*line;

	line = (char *)malloc(sizeof(char) + 1);
	while ((n = read(fd, line, 1)) > 0)
	{
		printf("n: %d\n", n);
		line[n] = '\0';
		printf("|%s|", line);
	}
	free(line);
	printf("\n");
}

static void	read_heredoc_child(t_ast *ast, int fd)
{
	char	*line;

	signal(SIGINT, handle_signal_heredoc);
	while (TRUE)
	{
		line = readline("> ");
		if (!line)
			exit(EXIT_SUCCESS);
		if (ft_strcmp(line, ast->left->token))
			ft_putendl_fd(line, fd);
		else
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		free(line);
	}
}

static int	read_heredoc(t_ast *ast, int fd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == ERROR)
		return (FALSE);
	else if (pid == 0)
		read_heredoc_child(ast, fd);
	else
	{
		if (waitpid(pid, &status, 0) == ERROR)
			return (FALSE);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		update_env("?", ft_itoa(status));
		if (status == 1)
			return (ERROR);
	}
	return (TRUE);
}

static int	sub_traverse_heredoc(t_ast *ast)
{
	int	fd;
	int	result;

	fd = open(HEREDOC_PATH, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == ERROR)
		return (FALSE);
	result = read_heredoc(ast, fd);
	if (close(fd) == ERROR)
		return (FALSE);
	if (!result || result == ERROR)
	{
		if (unlink(HEREDOC_PATH) == ERROR)
			return (FALSE);
		return (result);
	}
	fd = open(HEREDOC_PATH, O_RDONLY);
	if (fd == ERROR)
		return (FALSE);
	if (unlink(HEREDOC_PATH) == ERROR)
		return (FALSE);
	ast->fd = fd;
	return (TRUE);
}

int	traverse_heredoc(t_ast *ast)
{
	int	result;

	if (!ast || ast->type == T_CMD)
		return (TRUE);
	if (ast->type == T_RDR && ft_strlen(ast->token) == 2 && *ast->token == '<')
	{
		result = sub_traverse_heredoc(ast);
		if (!result || result == ERROR)
			return (result);
	}
	result = traverse_heredoc(ast->left);
	if (!result || result == ERROR)
		return (result);
	result = traverse_heredoc(ast->right);
	if (!result || result == ERROR)
		return (result);
	return (TRUE);
}

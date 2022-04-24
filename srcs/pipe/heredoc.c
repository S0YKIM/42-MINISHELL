/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:02:56 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/24 22:57:07 by sokim            ###   ########.fr       */
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

static void	handle_sigint(int signum)
{
	if (signum == SIGINT)
	{
		printf("\b\b  \b\b");
		update_env("?", ft_strdup("1"));
		exit(1);
	}
}

static int	read_heredoc(t_ast *ast, int fd)
{
	char	*line;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		while (TRUE)
		{
			signal(SIGINT, handle_sigint);
			line = readline("> ");
			if (!line)
				continue ;
			if (ft_strcmp(line, ast->left->token))
				ft_putendl_fd(line, fd);
			else
			{
				free(line);
				return (TRUE);
			}
			free(line);
		}
	}
	else
	{
		if (waitpid(pid, &status, 0) == ERROR)
			return (FALSE);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		update_env("?", ft_itoa(status));
		if (status == 1)
			return (FALSE);
		return (TRUE);
	}
}

int	traverse_heredoc(t_ast *ast)
{
	int	fd;
	int	ret;

	if (!ast || ast->type == T_CMD)
		return (TRUE);
	if (ast->type == T_RDR && ft_strlen(ast->token) == 2 && *ast->token == '<')
	{
		fd = open(HEREDOC_PATH, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == ERROR)
			return (FALSE);
		ret = read_heredoc(ast, fd);
		if (!ret)
			return (FALSE);
		if (close(fd) == ERROR)
			return (FALSE);
		fd = open(HEREDOC_PATH, O_RDONLY);
		if (fd == ERROR)
			return (FALSE);
		if (unlink(HEREDOC_PATH) == ERROR)
			return (FALSE);
		ast->fd = fd;
	}
	if (!traverse_heredoc(ast->left))
		return (FALSE);
	if (!traverse_heredoc(ast->right))
		return (FALSE);
	return (TRUE);
}

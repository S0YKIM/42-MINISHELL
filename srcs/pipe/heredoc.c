/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:02:56 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/19 17:02:13 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 나중에 지우기
// static void	read_fd(int fd)
// {
// 	int		n;
// 	char	*line;

// 	line = (char *)malloc(sizeof(char) + 1);
// 	while ((n = read(fd, line, 1)) > 0)
// 	{
// 		printf("n: %d\n", n);
// 		line[n] = '\0';
// 		printf("|%s|", line);
// 	}
// 	free(line);
// 	printf("\n");
// }

static void	read_heredoc(t_ast *ast, int fd)
{
	char	*line;

	while (TRUE)
	{
		line = readline("> ");
		if (!line)
			continue ;
		if (ft_strcmp(line, ast->left->token))
			ft_putendl_fd(line, fd);
		else
		{
			free(line);
			break ;
		}
		free(line);
	}
}

int	traverse_heredoc(t_ast *ast)
{
	int	fd;

	if (!ast || ast->type == T_CMD)
		return (TRUE);
	if (ast->type == T_RDR && ft_strlen(ast->token) == 2 && *ast->token == '<')
	{
		fd = open(HEREDOC_PATH, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == ERROR)
			return (FALSE);
		read_heredoc(ast, fd);
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

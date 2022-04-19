/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:02:56 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/18 22:26:28 by heehkim          ###   ########.fr       */
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
// 		line[n] = '\0';
// 		printf("|%s|", line);
// 	}
// 	free(line);
// 	printf("\n");
// }

static char	*make_heredoc_path(void)
{
	static int	num;
	char		*num_str;
	char		*path;

	num_str = ft_itoa(num++);
	if (!num_str)
		return (NULL);
	path = ft_strjoin(HEREDOC_PATH, num_str);
	free(num_str);
	return (path);
}

static void	read_heredoc(t_ast *ast, int fd)
{
	char		*line;

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

static int	set_heredoc_fd(t_ast *ast)
{
	int			fd;
	char		*path;

	path = make_heredoc_path();
	if (!path)
		return (FALSE);
	fd = open_outfile(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == ERROR)
		return (FALSE);
	read_heredoc(ast, fd);
	if (close(fd) == ERROR)
	{
		free(path);
		return (FALSE);
	}
	fd = open_infile(path, O_RDONLY);
	if (fd == ERROR)
		return (FALSE);
	if (unlink_file(path) == ERROR)
		return (FALSE);
	free(path);
	ast->fd = fd;
	return (TRUE);
}

int	traverse_heredoc(t_ast *ast)
{
	if (!ast || ast->type == T_CMD)
		return (TRUE);
	if (ast->type == T_RDR && ft_strlen(ast->token) == 2 && *ast->token == '<')
	{
		if (!set_heredoc_fd(ast))
			return (FALSE);
	}
	if (!traverse_heredoc(ast->left))
		return (FALSE);
	if (!traverse_heredoc(ast->right))
		return (FALSE);
	return (TRUE);
}

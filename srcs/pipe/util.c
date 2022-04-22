/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 22:22:22 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/22 22:44:38 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_print_error(char *path)
{
	ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (path)
	{
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	exit(EXIT_FAILURE);
}

int	open_infile(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == ERROR)
		exit_print_error(path);
	return (fd);
}

int	open_outfile(char *path, int flag)
{
	int	fd;

	fd = open(path, flag, 0644);
	if (fd == ERROR)
		exit_print_error(path);
	return (fd);
}

void	close_fd(int fd)
{
	if (close(fd) == ERROR)
		exit_print_error(NULL);
}

void	dup_fd(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == ERROR)
		exit_print_error(NULL);
}

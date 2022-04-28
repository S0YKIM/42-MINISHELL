/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 00:21:45 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/28 15:32:50 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_infile(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == ERROR)
		print_file_error(path);
	return (fd);
}

int	open_outfile(char *path, int flag)
{
	int	fd;

	fd = open(path, flag, 0644);
	if (fd == ERROR)
		print_file_error(path);
	return (fd);
}

int	close_fd(int fd)
{
	int	result;

	result = close(fd);
	if (result == ERROR)
		print_file_error(NULL);
	return (result);
}

int	dup_fd(int fd1, int fd2)
{
	int	result;

	result = dup2(fd1, fd2);
	if (result == ERROR)
		print_file_error(NULL);
	return (result);
}

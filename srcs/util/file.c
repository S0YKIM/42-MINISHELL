/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 17:11:16 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/18 17:18:16 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_infile(char *path, int flag)
{
	int	fd;

	fd = open(path, flag);
	if (fd == -1)
		free(path);
	return (fd);
}

int	open_outfile(char *path, int flag, mode_t mode)
{
	int	fd;

	fd = open(path, flag, mode);
	if (fd == -1)
		free(path);
	return (fd);
}

int	unlink_file(const char *path)
{
	int	result;

	result = unlink(path);
	if (result == -1)
		free(path);
	return (result);
}

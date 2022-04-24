/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 15:50:33 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/24 15:12:44 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

int		traverse_heredoc(t_ast *ast);
void	traverse_redirection(t_ast *ast, int *in_fd, int *out_fd);
int		fork_process(t_data *data);

int		execute(t_data *data);

int		open_infile(char *path);
int		open_outfile(char *path, int flag);
void	close_fd(int fd);
void	dup_fd(int fd1, int fd2);

// 나중에 삭제
void	read_fd(int fd);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 15:50:33 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/19 22:59:39 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

int	traverse_heredoc(t_ast *ast);

int	fork_process(t_data *data);

int	traverse_redirection(t_ast *ast, int *in_fd, int *out_fd);

// 나중에 삭제
void	read_fd(int fd);

#endif

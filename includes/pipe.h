/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 15:50:33 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/28 00:53:03 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

int		traverse_heredoc(t_ast *ast);
int		traverse_redirection(t_ast *ast, int *in_fd, int *out_fd);
int		fork_process(t_data *data);

int		execute(t_data *data);

void	close_parent_fds(t_data *data, int i);
void	close_child_fds(int in_fd, int out_fd, t_ast *curr, t_ast *prev);

#endif

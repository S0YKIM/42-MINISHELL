/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:02:20 by sokim             #+#    #+#             */
/*   Updated: 2022/04/28 01:00:35 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

int		exec_builtin(t_ast *ast, t_data *data);
void	execute_cmd(t_ast *ast, t_data *data);
int		execute_one_builtin(t_data *data);

#endif

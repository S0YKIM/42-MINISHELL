/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:02:20 by sokim             #+#    #+#             */
/*   Updated: 2022/04/30 21:21:22 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

int		exec_builtin(t_ast *ast);
void	execute_cmd(t_ast *ast);
int		execute_one_builtin(t_data *data);

#endif

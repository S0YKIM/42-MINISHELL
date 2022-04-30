/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:43:13 by sokim             #+#    #+#             */
/*   Updated: 2022/04/30 21:24:13 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "struct.h"

/*
 * Builtin functions
*/
int		ft_env(t_ast *ast);
int		ft_pwd(void);
int		ft_export(t_ast *ast);
int		ft_cd(t_ast *ast);
int		ft_unset(t_ast *ast);
int		ft_exit(t_ast *ast);
int		ft_echo(t_ast *ast);

/*
 * Util functions
*/
int		is_valid_key_name(char *key);
int		is_str_num(char *str);
int		is_str_long_long(char *str);

/*
 * Export utils
*/

t_env	*create_display_env_list(void);
void	display_env_list(t_env *display);

#endif

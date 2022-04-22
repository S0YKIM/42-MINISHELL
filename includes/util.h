/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:45:20 by sokim             #+#    #+#             */
/*   Updated: 2022/04/22 22:56:50 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

/*
 * Initialize data
*/
void	init_data(t_data *data);

/*
 * Free memory allocated
*/
void	free_env_list(void);
void	free_token_list(t_data *data);
void	free_astree(t_ast *ast);
int		free_double_pointer(char **tab);

/*
 * Print error messages
*/
void	print_invalid_identifier(char *cmd, char *argv);
void	print_full_no_such_file(char *cmd, char *argv);
void	print_no_such_file(char *cmd, char *argv);
void	print_not_set(char *cmd, char *argv);

#endif

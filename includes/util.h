/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:45:20 by sokim             #+#    #+#             */
/*   Updated: 2022/04/24 16:20:12 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

/*
 * Initialize data
*/
int		init(t_data *data, char **envp);

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

/*
 * Check error
 */
int		check_syntax_error(t_data *data);

#endif

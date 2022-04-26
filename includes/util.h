/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:45:20 by sokim             #+#    #+#             */
/*   Updated: 2022/04/27 01:37:40 by heehkim          ###   ########.fr       */
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
void	print_file_error(char *path);

/*
 * Check error
 */
int		check_syntax_error(t_data *data);

/*
 * File utils
 */
int		open_infile(char *path);
int		open_outfile(char *path, int flag);
int		close_fd(int fd);
int		dup_fd(int fd1, int fd2);

#endif

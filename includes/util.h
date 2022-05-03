/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:45:20 by sokim             #+#    #+#             */
/*   Updated: 2022/05/04 00:40:07 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

/*
 * Free memory allocated
 */
void	free_env_list(void);
void	free_token_list(t_data *data);
void	free_astree(t_ast *ast);
int		free_double_pointer(char **tab);
void	free_display_env_list(t_env **display);

/*
 * Print error messages
 */
void	print_invalid_identifier(char *cmd, char *arg);
void	print_no_such_file(char *cmd, char *arg, int shellname);
void	print_not_set(char *cmd, char *arg);
void	print_command_not_found(char *cmd);
void	print_file_error(char *path);

/*
 * Check utils
 */
int		check_syntax_error(t_data *data, char *line);
int		is_builtin(t_ast *node);

/*
 * File utils
 */
int		open_infile(char *path);
int		open_outfile(char *path, int flag);
int		close_fd(int fd);
int		dup_fd(int fd1, int fd2);

/*
 * Get next line
 */
int		get_next_line(int fd, char **line);

/*
 * Ascii art
 */
void	print_art(void);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:45:20 by sokim             #+#    #+#             */
/*   Updated: 2022/04/18 20:46:26 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

void	init_data(t_data *data);

void	free_env_list(t_data *data);
void	free_token_list(t_data *data);
void	free_astree(t_ast *ast);

int		open_infile(char *path, int flag);
int		open_outfile(char *path, int flag, mode_t mode);
int		unlink_file(char *path);

#endif

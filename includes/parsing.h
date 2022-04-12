/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 19:17:43 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/12 23:10:28 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "struct.h"

int		add_env_node(t_data *data, char *env);
int		parse_env(char **envp, t_data *data);
void	free_env_list(t_data *data);
int		tokenize(t_data *data, char *line);
void	free_token_list(t_data *data);
int		trim_token(t_data *data);
int		expand_env(t_data *data, t_token *curr);

#endif

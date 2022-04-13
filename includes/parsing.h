/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 19:17:43 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/13 16:56:26 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "struct.h"

int		parse_env(char **envp, t_data *data);
void	free_env_list(t_data *data);
int		tokenize(t_data *data, char *line);
void	free_token_list(t_data *data);
int		trim_token(t_data *data);
int		expand_env(t_data *data, t_token *curr);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 19:17:43 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/14 21:25:58 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "struct.h"

int		parse_env(char **envp, t_data *data);

int		tokenize(t_data *data, char *line);

int		trim_token(t_data *data);

int		expand_env(t_data *data, t_token *curr);

int		create_astree(t_data *data);
t_ast	*create_ast_node(t_token *curr);

t_ast	*add_ast_node(t_ast *parent, t_ast *new);

#endif

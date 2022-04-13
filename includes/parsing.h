/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 19:17:43 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/13 23:06:43 by heehkim          ###   ########.fr       */
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

int		create_astree(t_data *data);
t_ast	*create_ast_node(t_token *curr);
void	free_astree(t_data *data, t_ast *ast);

t_ast	*add_ast_node(t_ast *parent, t_ast *new);

#endif

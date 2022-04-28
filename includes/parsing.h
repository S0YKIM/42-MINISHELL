/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 19:17:43 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/27 20:03:25 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "struct.h"

int		parse_env(char **envp);

int		tokenize(t_data *data, char *line);
void	delete_token_node(t_data *data, t_token **node);
int		trim_token(t_data *data);
int		expand_env(t_token *curr);
char	*expand_env_value(char *i, char **key_end, int is_dquote);

int		create_astree(t_data *data);
t_ast	*create_ast_node(t_token *curr);
t_ast	*add_ast_node(t_ast *parent, t_ast *new);
int		simplify_astree(t_data *data, t_ast *node);

// 나중에 삭제
void	display_env_list(void);
void	display_token_list(t_data *data);
void	display_astree(t_ast *ast);

#endif

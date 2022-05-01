/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 19:17:43 by heehkim           #+#    #+#             */
/*   Updated: 2022/05/01 20:42:38 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "struct.h"

int		parse_env(char **envp);

int		tokenize(t_data *data, char *line);
void	delete_token_node(t_data *data, t_token **node);
int		insert_token_node(t_token **curr, char *data);

int		trim_token(t_data *data);
int		trim_quote(t_token *curr);

int		expand(t_data *data, t_token **curr);
int		expand_env(t_token **curr);
char	*expand_env_value(char *i, char **key_end, int is_dquote);
int		expand_tilde(t_token *curr);
int		replace_token_substr(t_token *curr, char *key_start);
int		split_value_with_space( \
			t_token **curr, char *value, char *key_start, char *key_end);
int		handle_invalid_env(t_token **curr, char *value, char *key_start);
int		has_tilde(char *arg);

int		create_astree(t_data *data);
t_ast	*create_ast_node(t_token *curr);
t_ast	*add_ast_node(t_ast *parent, t_ast *new);
int		simplify_astree(t_data *data, t_ast *node);

#endif

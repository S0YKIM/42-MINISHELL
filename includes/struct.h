/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:44:51 by sokim             #+#    #+#             */
/*   Updated: 2022/04/19 14:36:20 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	char			*data;
	int				is_word;
	struct s_token	*next;
}	t_token;

typedef struct s_ast
{
	char			*token;
	int				argc;
	char			**argv;
	int				type;
	int				fd;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_data
{
	t_token	*token_list;
	t_ast	*astree;
}	t_data;

t_env	*g_env_list;

#endif

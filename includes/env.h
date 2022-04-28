/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 13:34:53 by sokim             #+#    #+#             */
/*   Updated: 2022/04/28 15:33:11 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "struct.h"

/*
 * Change envrionment variables
*/
int		update_env(char *key, char *value);
void	remove_node(t_env **node);

/*
 * Search environment variables list
*/
t_env	*get_node_with_key(char *key);
char	*get_env_value(char *key);
int		is_there_node_with_key(char *key);

/*
 * Make envp
*/
char	**make_envp(void);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 13:34:53 by sokim             #+#    #+#             */
/*   Updated: 2022/04/10 13:43:40 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

#include "struct.h"

int		update_env(t_data *data, char *key, char *value);
char	*get_env_value(t_data *data, char *key);

#endif

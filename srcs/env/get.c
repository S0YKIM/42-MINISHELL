/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 13:42:35 by sokim             #+#    #+#             */
/*   Updated: 2022/04/10 13:54:36 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_data *data, char *key)
{
	t_env	*curr;

	curr = data->env_list;
	while (curr)
	{
		if (!ft_strncmp(curr->key, key, ft_strlen(key)))
			return (ft_strdup(curr->value));
		curr = curr->next;
	}
	return ("");
}
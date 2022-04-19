/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 13:42:35 by sokim             #+#    #+#             */
/*   Updated: 2022/04/19 14:56:11 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*get_node_with_key(char *key)
{
	t_env	*curr;

	curr = g_env_list;
	while (curr)
	{
		if (!ft_strcmp(curr->key, key))
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

char	*get_env_value(char *key)
{
	t_env	*curr;

	curr = g_env_list;
	while (curr)
	{
		if (!ft_strcmp(curr->key, key))
			return (ft_strdup(curr->value));
		curr = curr->next;
	}
	return (ft_strdup(""));
}

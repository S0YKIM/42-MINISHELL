/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 13:42:35 by sokim             #+#    #+#             */
/*   Updated: 2022/04/30 23:05:12 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_there_node_with_key(char *key)
{
	t_env	*curr;

	curr = g_env_list;
	while (curr)
	{
		if (!ft_strcmp(curr->key, key))
			return (TRUE);
		curr = curr->next;
	}
	return (FALSE);
}

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
		{
			if (!curr->value)
				return (ft_strdup(""));
			return (ft_strdup(curr->value));
		}
		curr = curr->next;
	}
	return (ft_strdup(""));
}

int	is_there_env_value(char *key)
{
	t_env	*curr;

	curr = g_env_list;
	while (curr)
	{
		if (!ft_strcmp(curr->key, key))
		{
			if (!curr->value)
				return (FALSE);
			return (TRUE);
		}
		curr = curr->next;
	}
	return (FALSE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 13:08:27 by sokim             #+#    #+#             */
/*   Updated: 2022/04/30 19:25:35 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_new_env_node(char *key, char *value)
{
	t_env	*new;
	t_env	*curr;

	new = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!new)
		return (FALSE);
	new->key = key;
	new->value = value;
	if (!g_env_list)
		g_env_list = new;
	else
	{
		curr = g_env_list;
		while (curr->next)
			curr = curr->next;
		new->prev = curr;
		curr->next = new;
	}
	return (TRUE);
}

static void	change_value(char *key, char *value)
{
	t_env	*curr;
	char	*tmp;

	if (!value)
		return ;
	curr = g_env_list;
	while (curr)
	{
		if (!ft_strcmp(curr->key, key))
		{
			tmp = curr->value;
			curr->value = value;
			free(tmp);
			return ;
		}
		curr = curr->next;
	}
}

int	update_env(char *key, char *value)
{
	if (is_there_node_with_key(key))
	{
		change_value(key, value);
		if (ft_strcmp(key, "?") && ft_strcmp(key, "PWD") \
			&& ft_strcmp(key, "OLDPWD") && ft_strcmp(key, "~"))
			free(key);
		return (TRUE);
	}
	if (!add_new_env_node(key, value))
		return (FALSE);
	return (TRUE);
}

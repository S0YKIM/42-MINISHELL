/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 13:08:27 by sokim             #+#    #+#             */
/*   Updated: 2022/04/28 16:28:44 by sokim            ###   ########.fr       */
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

static int	change_value(char *key, char *value)
{
	t_env	*curr;
	char	*tmp;

	curr = g_env_list;
	while (curr)
	{
		if (!ft_strcmp(curr->key, key))
		{
			if (!value)
				return (TRUE);
			tmp = curr->value;
			curr->value = value;
			free(tmp);
			return (TRUE);
		}
		curr = curr->next;
	}
	return (FALSE);
}

int	update_env(char *key, char *value)
{
	if (change_value(key, value) == TRUE)
		return (TRUE);
	if (add_new_env_node(key, value) == FALSE)
		return (FALSE);
	return (TRUE);
}

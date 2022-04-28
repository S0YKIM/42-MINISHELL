/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 13:08:27 by sokim             #+#    #+#             */
/*   Updated: 2022/04/28 15:35:52 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_new_env_node(t_data *data, char *key, char *value)
{
	t_env	*new;
	t_env	*curr;

	new = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!new)
		return (FALSE);
	new->key = key;
	new->value = value;
	if (!data->env_list)
		data->env_list = new;
	else
	{
		curr = data->env_list;
		while (curr->next)
			curr = curr->next;
		new->prev = curr;
		curr->next = new;
	}
	return (TRUE);
}

static int	insert_new_env_node(t_env *curr, char *key, char *value)
{
	t_env	*new;

	new = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!new)
		return (FALSE);
	new->key = key;
	new->value = value;
	new->prev = curr->prev;
	new->next = curr;
	if (curr->prev)
		curr->prev->next = new;
	curr->prev = new;
	return (TRUE);
}

static int	change_value(t_env *curr, char *value)
{
	char	*tmp;

	if (!value)
		return (TRUE);
	tmp = curr->value;
	curr->value = value;
	free(tmp);
	return (TRUE);
}

int	update_env(t_data *data, char *key, char *value)
{
	t_env	*curr;

	curr = data->env_list;
	while (curr)
	{
		if (!ft_strcmp(key, curr->key))
			return (change_value(curr, value));
		else if (ft_strcmp(key, curr->key) < 0)
			return (insert_new_env_node(curr, key, value));
		curr = curr->next;
	}
	return (add_new_env_node(data, key, value));
}

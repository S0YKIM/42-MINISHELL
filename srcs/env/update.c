/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 13:08:27 by sokim             #+#    #+#             */
/*   Updated: 2022/04/15 16:59:02 by sokim            ###   ########.fr       */
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
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
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

static int	change_value(t_data *data, char *key, char *value)
{
	t_env	*curr;
	char	*tmp;

	curr = data->env_list;
	while (curr)
	{
		if (!ft_strcmp(curr->key, key))
		{
			tmp = curr->value;
			curr->value = ft_strdup(value);
			free(tmp);
			return (TRUE);
		}
		curr = curr->next;
	}
	return (FALSE);
}

int	update_env(t_data *data, char *key, char *value)
{
	if (change_value(data, key, value) == TRUE)
		return (TRUE);
	if (add_new_env_node(data, key, value) == FALSE)
		return (FALSE);
	return (TRUE);
}

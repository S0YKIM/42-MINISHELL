/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 13:08:27 by sokim             #+#    #+#             */
/*   Updated: 2022/04/13 01:36:24 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*add_new_env_node(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

static int	change_value(t_env **curr, char *key, char *value)
{
	char	*tmp;

	while (*curr)
	{
		if (!ft_strncmp((*curr)->key, key, ft_strlen(key)))
		{
			tmp = (*curr)->value;
			(*curr)->value = ft_strdup(value);
			free(tmp);
			return (SUCCESS);
		}
		if (!(*curr)->next)
			break ;
		*curr = (*curr)->next;
	}
	return (FAILURE);
}

int	update_env(t_data *data, char *key, char *value)
{
	t_env	*curr;

	curr = data->env_list;
	if (!curr)
	{
		data->env_list = add_new_env_node(key, value);
		if (!data->env_list)
			return (FAILURE);
	}
	else if (change_value(&curr, key, value) == SUCCESS)
		return (SUCCESS);
	else
		if (!(curr->next = add_new_env_node(key, value)))
			return (FAILURE);
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 13:08:27 by sokim             #+#    #+#             */
/*   Updated: 2022/04/10 13:54:55 by sokim            ###   ########.fr       */
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

int	update_env(t_data *data, char *key, char *value)
{
	t_env	*curr;
	char	*tmp;

	curr = data->env_list;
	while (curr)
	{
		if (!ft_strncmp(curr->key, key, ft_strlen(key)))
		{
			tmp = curr->value;
			curr->value = ft_strdup(value);
			free(tmp);
			if (!curr->value)
				return (EXIT_FAILURE);
			break ;
		}
		curr = curr->next;
	}
	if (!curr)
	{
		curr = add_new_env_node(key, value);
		if (!curr)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:22:06 by sokim             #+#    #+#             */
/*   Updated: 2022/04/30 19:44:05 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_new_env_node(char *key, char *value, t_env **display)
{
	t_env	*new;
	t_env	*curr;

	new = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!new)
		return (FALSE);
	new->key = key;
	new->value = value;
	if (!*display)
		*display = new;
	else
	{
		curr = *display;
		while (curr->next)
			curr = curr->next;
		new->prev = curr;
		curr->next = new;
	}
	return (TRUE);
}

static int	insert_new_env_node(t_env *curr, char *key, \
	char *value, t_env **display)
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
	else
		*display = new;
	curr->prev = new;
	return (TRUE);
}

static int	add_env_to_display(char *key, char *value, t_env **display)
{
	t_env	*curr;

	curr = *display;
	while (curr)
	{
		if (ft_strcmp(key, curr->key) < 0)
			return (insert_new_env_node(curr, key, value, display));
		curr = curr->next;
	}
	return (add_new_env_node(key, value, display));
}

t_env	*create_display_env_list(void)
{
	t_env	*display;
	t_env	*curr;
	char	*key;
	char	*value;

	display = NULL;
	curr = g_env_list;
	while (curr)
	{
		key = ft_strdup(curr->key);
		value = ft_strdup(curr->value);
		if (!add_env_to_display(key, value, &display))
			return (NULL);
		curr = curr->next;
	}
	return (display);
}

void	display_env_list(t_env *display)
{
	t_env	*curr;

	curr = display;
	while (curr)
	{
		if (*(curr->key) == '?' || *(curr->key) == '~')
		{
			curr = curr->next;
			continue ;
		}
		else if (curr->value)
			printf("declare -x %s=\"%s\"\n", curr->key, curr->value);
		else
			printf("declare -x %s\n", curr->key);
		curr = curr->next;
	}
}

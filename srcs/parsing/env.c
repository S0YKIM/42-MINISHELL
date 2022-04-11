/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:51:17 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/11 22:31:28 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 나중에 삭제!
// static void	display_list(t_data *data)
// {
// 	t_env	*curr;

// 	curr = data->env_list;
// 	while (curr)
// 	{
// 		printf("key: %s | value: %s\n", curr->key, curr->value);
// 		curr = curr->next;
// 	}
// }

void	free_env_list(t_data *data)
{
	t_env	*curr;
	t_env	*next;

	curr = data->env_list;
	while (curr)
	{
		next = curr->next;
		free(curr->key);
		free(curr->value);
		free(curr);
		curr = next;
	}
	data->env_list = NULL;
}

static int	set_key_value(char *env, char **key, char **value)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i] == '=')
		{
			env[i] = '\0';
			*key = ft_strdup(env);
			if (!*key)
				return (FALSE);
			*value = ft_strdup(env + i + 1);
			if (!*value)
			{
				free(*key);
				return (FALSE);
			}
		}
		i++;
	}
	return (TRUE);
}

int	add_env_node(t_data *data, char *env)
{
	t_env	*new;
	t_env	*curr;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (FALSE);
	set_key_value(env, &new->key, &new->value);
	new->next = NULL;
	if (!data->env_list)
		data->env_list = new;
	else
	{
		curr = data->env_list;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
	return (TRUE);
}

int	parse_env(char **envp, t_data *data)
{
	int		i;

	i = 0;
	while (envp && envp[i])
	{
		if (!add_env_node(data, envp[i]))
		{
			free_env_list(data);
			return (FALSE);
		}
		i++;
	}
	// display_list(data);
	return (TRUE);
}

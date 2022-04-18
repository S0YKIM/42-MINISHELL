/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:51:17 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/18 20:41:01 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 나중에 삭제!
void	display_env_list(t_data *data)
{
	t_env	*curr;

	curr = data->env_list;
	while (curr)
	{
		printf("key: %s | value: %s\n", curr->key, curr->value);
		curr = curr->next;
	}
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

static int	add_prev_exit_env(t_data *data)
{
	char	*key;
	char	*value;

	key = ft_strdup("?");
	if (!key)
		return (FALSE);
	value = ft_strdup("0");
	if (!value)
	{
		free(key);
		return (FALSE);
	}
	if (!update_env(data, key, value))
	{
		free_env_list(data);
		return (FALSE);
	}
	return (TRUE);
}

int	parse_env(char **envp, t_data *data)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (envp && envp[i])
	{
		if (set_key_value(envp[i], &key, &value))
		{
			if (!update_env(data, key, value))
			{
				free_env_list(data);
				return (FALSE);
			}
		}
		i++;
	}
	if (!add_prev_exit_env(data))
		return (FALSE);
	// display_list(data);
	return (TRUE);
}

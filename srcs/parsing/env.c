/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:51:17 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/28 17:38:06 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 나중에 삭제!
// void	display_env_list(void)
// {
// 	t_env	*curr;

// 	curr = g_env_list;
// 	while (curr)
// 	{
// 		printf("key: %s | value: %s\n", curr->key, curr->value);
// 		curr = curr->next;
// 	}
// }

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

static int	add_prev_exit_env(void)
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
	if (!update_env(key, value))
	{
		free_env_list();
		return (FALSE);
	}
	return (TRUE);
}

int	parse_env(char **envp)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (envp && envp[i])
	{
		if (set_key_value(envp[i], &key, &value))
		{
			if (!update_env(key, value))
			{
				free_env_list();
				return (FALSE);
			}
		}
		i++;
	}
	if (!add_prev_exit_env())
		return (FALSE);
	// display_list(data);
	return (TRUE);
}

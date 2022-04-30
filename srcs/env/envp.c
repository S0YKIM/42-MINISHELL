/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 00:13:18 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/30 19:52:36 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_env_list_len(void)
{
	int		i;
	t_env	*curr;

	i = 0;
	curr = g_env_list;
	while (curr)
	{
		if (ft_strcmp(curr->key, "?") && ft_strcmp(curr->key, "~"))
			i++;
		curr = curr->next;
	}
	return (i);
}

static char	*join_key_value(t_env *curr)
{
	char	*env;
	char	*tmp;

	if (!curr->value)
	{
		env = ft_strdup(curr->key);
		return (env);
	}
	env = ft_strjoin(curr->key, "=");
	if (!env)
		return (NULL);
	tmp = env;
	env = ft_strjoin(env, curr->value);
	free(tmp);
	return (env);
}

char	**make_envp(void)
{
	char	**envp;
	t_env	*curr;
	int		i;
	char	*env;

	envp = (char **)ft_calloc(get_env_list_len() + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	curr = g_env_list;
	i = 0;
	while (curr)
	{
		if (ft_strcmp(curr->key, "?") && ft_strcmp(curr->key, "~"))
		{
			env = join_key_value(curr);
			if (!env)
			{
				free_double_pointer(envp);
				return (NULL);
			}
			envp[i++] = env;
		}
		curr = curr->next;
	}
	return (envp);
}

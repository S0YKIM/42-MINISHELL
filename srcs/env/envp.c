/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 21:43:12 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/26 22:21:57 by heehkim          ###   ########.fr       */
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
		if (ft_strcmp(curr->key, "?") && curr->value)
			i++;
		curr = curr->next;
	}
	return (i);
}

static char	*join_key_value(t_env *curr)
{
	char	*env;
	char	*tmp;

	env = ft_strjoin(curr->key, "=");
	if (!env)
		return (NULL);
	tmp = env;
	env = ft_strjoin(env, curr->value);
	free(tmp);
	if (!env)
		return (NULL);
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
		if (ft_strcmp(curr->key, "?") && curr->value)
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

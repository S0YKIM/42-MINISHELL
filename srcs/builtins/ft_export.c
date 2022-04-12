/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:11:19 by sokim             #+#    #+#             */
/*   Updated: 2022/04/12 21:54:04 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_only(t_env *env_list)
{
	t_env	*curr;

	curr = env_list;
	while (curr)
	{
		if (!ft_strncmp(curr->key, "?", 1))
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
	return (SUCCESS);
}

static char	*get_key_name(char *str)
{
	char	*key;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			str[i] = '\0';
			break ;
		}
		i++;
	}
	key = ft_strdup(str);
	return (key);
}

static int	is_valid_key_name(char *key)
{
	if (!key || !key[0])
		return (FALSE);
	if (ft_isdigit(key[0]))
		return (FALSE);
	if (ft_strchr(key, '?'))
		return (FALSE);
	return (TRUE);
}

int	ft_export(char **cmds, t_data *data)
{
	char	*key;

	if (!cmds[1])
		return (export_only(data->env_list));
	key = get_key_name(cmds[1]);
	if (!is_valid_key_name(key))
	{
		free(key);
		printf("export: `%s`: not a valid identifier\n", cmds[1]);
		return (FAILURE);
	}
	free(key);
	add_env_node(data, cmds[1]);
	return (SUCCESS);
}

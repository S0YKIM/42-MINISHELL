/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:11:19 by sokim             #+#    #+#             */
/*   Updated: 2022/04/13 18:52:16 by sokim            ###   ########.fr       */
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

static char	*get_value_in_arg(char *str)
{
	char	*value;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			i++;
			value = ft_strdup(str);
			return (value);
		}
		i++;
	}
	return (NULL);
}

int	ft_export(char **cmds, t_data *data)
{
	char	*key;
	char	*value;
	int		i;
	int		ret;

	if (!cmds[1])
		return (export_only(data->env_list));
	i = 0;
	ret = SUCCESS;
	while (cmds[++i])
	{
		key = get_key_name(cmds[i]);
		if (!is_valid_key_name(key))
		{
			printf("export: `%s': not a valid identifier\n", cmds[1]);
			ret = FAILURE;
		}
		else
		{
			value = get_value_in_arg(cmds[1]);
			if (!update_env(data, key, value))
				ret = FAILURE;
		}
		free(key);
		free(value);
	}
	return (ret);
}

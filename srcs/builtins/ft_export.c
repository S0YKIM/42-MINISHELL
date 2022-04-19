/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:11:19 by sokim             #+#    #+#             */
/*   Updated: 2022/04/19 15:06:10 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_only(void)
{
	t_env	*curr;

	curr = g_env_list;
	while (curr)
	{
		if (*(curr->key) == '?')
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
	char	*tmp;
	int		i;

	tmp = ft_strdup(str);
	if (!tmp)
		return (NULL);
	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == '=')
		{
			tmp[i] = '\0';
			break ;
		}
		i++;
	}
	key = ft_strdup(tmp);
	free(tmp);
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
			value = ft_strdup(str + i);
			return (value);
		}
		i++;
	}
	return (NULL);
}

int	ft_export(t_ast *ast)
{
	char	*key;
	char	*value;
	int		i;
	int		ret;

	if (ast->argc == 1)
		return (export_only());
	i = 0;
	ret = SUCCESS;
	while (++i < ast->argc)
	{
		key = get_key_name(ast->argv[i]);
		if (!is_valid_key_name(key))
		{
			printf("microshell: export: `%s': \
			not a valid identifier\n", ast->argv[i]);
			ret = FAILURE;
		}
		else if (*key != '_')
		{
			value = get_value_in_arg(ast->argv[i]);
			if (!update_env(key, value))
				ret = FAILURE;
		}
	}
	return (ret);
}

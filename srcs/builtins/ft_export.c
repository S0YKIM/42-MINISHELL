/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:11:19 by sokim             #+#    #+#             */
/*   Updated: 2022/04/30 01:42:06 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_only(void)
{
	t_env	*display;

	display = create_display_env_list();
	if (!display)
	{
		free_display_env_list(&display);
		return (FAILURE);
	}
	display_env_list(display);
	free_display_env_list(&display);
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

static int	export_multi(t_ast *ast)
{
	char	*key;
	char	*value;
	int		i;
	int		ret;

	i = 0;
	ret = SUCCESS;
	while (++i < ast->argc)
	{
		key = get_key_name(ast->argv[i]);
		if (!is_valid_key_name(key))
		{
			print_invalid_identifier("export", ast->argv[i]);
			free(key);
			ret = FAILURE;
		}
		else if (ft_strcmp(key, "_"))
		{
			value = get_value_in_arg(ast->argv[i]);
			if (!update_env(key, value))
				ret = FAILURE;
		}
	}
	return (ret);
}

int	ft_export(t_ast *ast)
{
	if (ast->argc == 1)
		return (export_only());
	else
		return (export_multi(ast));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:11:19 by sokim             #+#    #+#             */
/*   Updated: 2022/04/07 18:23:03 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_only(t_env *env_list)
{
	t_env	*curr;

	curr = env_list;
	while (curr)
	{
		if (curr->value)
			printf("declare -x %s=%s\n", curr->key, curr->value);
		else
			printf("declare -x %s\n", curr->key);
		curr = curr->next;
	}
	return (EXIT_SUCCESS);
}

int	ft_export(char **cmds, t_env *env_list)
{
	if (!cmds[1])
		return (export_only(env_list));
}

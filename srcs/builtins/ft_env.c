/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:53:17 by sokim             #+#    #+#             */
/*   Updated: 2022/04/19 15:04:02 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_ast *ast)
{
	t_env	*curr;

	if (ast->argc > 1)
	{
		printf("env: %s: No such file or directory\n", ast->argv[1]);
		return (127);
	}
	curr = g_env_list;
	while (curr)
	{
		if (*(curr->key) == '?')
		{
			curr = curr->next;
			continue ;
		}
		else if (curr->value)
			printf("%s=%s\n", curr->key, curr->value);
		curr = curr->next;
	}
	return (SUCCESS);
}

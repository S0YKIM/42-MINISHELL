/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:53:17 by sokim             #+#    #+#             */
/*   Updated: 2022/04/13 02:39:00 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **cmds, t_data *data)
{
	t_env	*curr;

	if (cmds[1])
	{
		printf("env: %s: No such file or directory\n", cmds[1]);
		return (127);
	}
	curr = data->env_list;
	while (curr)
	{
		if (!ft_strncmp(curr->key, "?", 1))
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

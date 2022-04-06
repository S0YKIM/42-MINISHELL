/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:53:17 by sokim             #+#    #+#             */
/*   Updated: 2022/04/06 19:20:09 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_env(t_env *env_list)
{
    t_env   *curr;

	curr = env_list;
	while (curr)
	{
		printf("%s=%s\n", curr->key, curr->value);
		curr = curr->next;
	}
	return (EXIT_SUCCESS);
}
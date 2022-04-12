/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 23:38:55 by sokim             #+#    #+#             */
/*   Updated: 2022/04/12 23:42:21 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_key_name(char *key)
{
	if (!key || !key[0])
		return (FALSE);
	if (ft_isdigit(key[0]))
		return (FALSE);
	if (ft_strchr(key, '?'))
		return (FALSE);
	return (TRUE);
}

int	print_error_msg(char **cmds)
{
	int	i;

	if (!cmds[2])
		return (SUCCESS);
	i = 2;
	while (cmds[i])
	{
		printf("%s: `%s': not a valid identifier\n", cmds[0], cmds[i]);
		i++;
	}
	return (FAILURE);
}

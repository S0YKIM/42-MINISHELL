/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 23:27:30 by sokim             #+#    #+#             */
/*   Updated: 2022/04/13 02:13:43 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **cmds, t_data *data)
{
	t_env	*node;
	int		ret;
	int		i;

	i = 0;
	while (cmds[++i])
	{
		if (!is_valid_key_name(cmds[i]))
		{
			printf("unset: `%s': not a valid identifier\n", cmds[i]);
			ret = FAILURE;
		}
		else
		{
			if (node = get_node_with_key(data, cmds[i]))
			{
				remove_node(node);
				ret = SUCCESS;
			}
		}
	}
	return (ret);
}

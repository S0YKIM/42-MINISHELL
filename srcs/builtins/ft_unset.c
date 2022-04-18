/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 23:27:30 by sokim             #+#    #+#             */
/*   Updated: 2022/04/18 14:13:51 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **cmds, t_data *data)
{
	t_env	*node;
	int		ret;
	int		i;

	i = 0;
	ret = SUCCESS;
	while (cmds[++i])
	{
		if (!is_valid_key_name(cmds[i]))
		{
			printf("microshell: unset: `%s': not a valid identifier\n", cmds[i]);
			ret = FAILURE;
		}
		else
		{
			node = get_node_with_key(data, cmds[i]);
			if (node)
				remove_node(node);
		}
	}
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 23:27:30 by sokim             #+#    #+#             */
/*   Updated: 2022/04/19 13:43:42 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_ast *ast, t_data *data)
{
	t_env	*node;
	int		ret;
	int		i;

	i = 0;
	ret = SUCCESS;
	while (ast->argv[++i])
	{
		if (!is_valid_key_name(ast->argv[i]))
		{
			printf("microshell: unset: `%s': \
			not a valid identifier\n", ast->argv[i]);
			ret = FAILURE;
		}
		else if (*(ast->argv[i]) != '_')
		{
			node = get_node_with_key(data, ast->argv[i]);
			if (node)
				remove_node(node);
		}
	}
	return (ret);
}

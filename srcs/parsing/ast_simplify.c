/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_simplify.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 21:37:31 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/24 15:30:33 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_ast_argv(t_ast *node, int len)
{
	node->argc = len;
	node->argv = (char **)ft_calloc(len + 1, sizeof(char *));
	if (!node->argv)
		return (FALSE);
	(node->argv)[0] = ft_strdup(node->token);
	if (!(node->argv)[0])
		return (FALSE);
	return (TRUE);
}

static int	merge_cmd_node(t_ast *node)
{
	int	i;

	if (!node->right)
	{
		if (!init_ast_argv(node, 1))
			return (FALSE);
		return (TRUE);
	}
	if (!merge_cmd_node(node->right))
		return (FALSE);
	if (!init_ast_argv(node, node->right->argc + 1))
		return (FALSE);
	i = 0;
	while (++i < node->argc)
	{
		(node->argv)[i] = ft_strdup(node->right->argv[i - 1]);
		if (!(node->argv)[i])
			return (FALSE);
	}
	free_astree(node->right);
	node->right = NULL;
	return (TRUE);
}

int	simplify_astree(t_data *data, t_ast *node)
{
	int	result;

	result = TRUE;
	if (!node || node->type < T_PL)
		return (TRUE);
	if (node->type == T_PL)
	{
		(data->pl_cnt)++;
		if (node->right)
			result = merge_cmd_node(node->right);
	}
	else
	{
		result = simplify_astree(data, node->left);
		if (!result)
			return (FALSE);
		result = simplify_astree(data, node->right);
	}
	return (result);
}

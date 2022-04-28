/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 16:14:22 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/28 15:32:45 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	traverse_syntax_error(t_ast *node)
{
	if (!node || node->type == T_CMD)
		return (TRUE);
	if (node->type == T_PIPE)
	{
		if (!node->left && !node->right)
			return (FALSE);
	}
	else if (node->type == T_RDR)
	{
		if (!node->left)
			return (FALSE);
	}
	if (!traverse_syntax_error(node->left))
		return (FALSE);
	return (traverse_syntax_error(node->right));
}

static int	print_syntax_error(void)
{
	ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
	ft_putendl_fd(": syntax error", STDERR_FILENO);
	return (FALSE);
}

int	check_syntax_error(t_data *data)
{
	t_ast	*node;

	node = data->astree;
	if (node->type == T_PIPE && !node->right)
		return (print_syntax_error());
	if (!traverse_syntax_error(node->left))
		return (print_syntax_error());
	if (!traverse_syntax_error(node->right))
		return (print_syntax_error());
	return (TRUE);
}

int	is_builtin(t_ast *node)
{
	char	*token;

	if (!node || !node->right)
		return (FALSE);
	token = node->right->token;
	if (!ft_strcmp(token, "cd") || !ft_strcmp(token, "echo") \
		|| !ft_strcmp(token, "env") || !ft_strcmp(token, "exit") \
		|| !ft_strcmp(token, "export") || !ft_strcmp(token, "pwd") \
		|| !ft_strcmp(token, "unset"))
		return (TRUE);
	return (FALSE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 23:04:49 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/14 00:42:39 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast	*add_ast_node_greater(t_ast *parent, t_ast *new)
{
	if (!new->left)
		new->left = parent;
	else
		new->right = parent;
	return (new);
}

static t_ast	*add_ast_node_equal(t_ast *parent, t_ast *new)
{
	if (!parent->right)
		parent->right = new;
	else
		parent->right = add_ast_node(parent->right, new);
	return (parent);
}

static void	add_ast_node_less_pl(t_ast *parent, t_ast *new)
{
	t_ast	*result;

	if (new->type == T_RDR)
	{
		if (!parent->left)
			parent->left = new;
		else
			add_ast_node(parent->left, new);
	}
	else if (new->type == T_CMD)
	{
		result = NULL;
		if (parent->left)
			result = add_ast_node(parent->left, new);
		if (!result)
		{
			if (!parent->right)
				parent->right = new;
			else
				add_ast_node(parent->right, new);
		}
	}
}

static t_ast	*add_ast_node_less(t_ast *parent, t_ast *new)
{
	if (parent->type == T_PL)
		add_ast_node_less_pl(parent, new);
	else if (parent->type == T_PIPE)
	{
		if (!parent->right)
			parent->right = create_ast_node(NULL);
		add_ast_node(parent->right, new);
	}
	else if (parent->type == T_RDR)
	{
		if (!parent->left)
			parent->left = new;
		else
			return (add_ast_node(parent->right, new));
	}
	return (parent);
}

t_ast	*add_ast_node(t_ast *parent, t_ast *new)
{
	if (!parent)
		return (NULL);
	if (parent->type < new->type)
		parent = add_ast_node_greater(parent, new);
	else if (parent->type == new->type)
		parent = add_ast_node_equal(parent, new);
	else if (parent->type > new->type)
		parent = add_ast_node_less(parent, new);
	return (parent);
}

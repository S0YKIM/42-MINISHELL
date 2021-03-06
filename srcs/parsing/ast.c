/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:27:32 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/29 18:11:48 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_token_type(t_ast *node, int is_word)
{
	if (is_word)
		node->type = T_CMD;
	else
	{
		if (*node->token == '|')
			node->type = T_PIPE;
		else if (ft_strchr("<>", *node->token))
			node->type = T_RDR;
	}
}

t_ast	*create_ast_node(t_token *curr)
{
	t_ast	*new;

	new = (t_ast *)ft_calloc(1, sizeof(t_ast));
	if (!new)
		return (NULL);
	if (!curr)
		new->type = T_PL;
	else
	{
		new->token = curr->data;
		set_token_type(new, curr->is_word);
		if (new->type == T_RDR)
			new->fd = -1;
	}
	return (new);
}

int	create_astree(t_data *data)
{
	t_token	*curr;
	t_ast	*new;
	t_ast	*root;

	data->astree = create_ast_node(NULL);
	if (!data->astree)
		return (FALSE);
	curr = data->token_list;
	while (curr)
	{
		new = create_ast_node(curr);
		root = add_ast_node(data->astree, new);
		if (!root)
			return (FALSE);
		data->astree = root;
		curr = curr->next;
	}
	if (!simplify_astree(data, data->astree))
		return (FALSE);
	return (TRUE);
}

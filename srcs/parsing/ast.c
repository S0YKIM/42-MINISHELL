/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:27:32 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/14 22:07:02 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 나중에 삭제
// void	display_astree(t_ast *ast)
// {
// 	int	i;

// 	if (!ast)
// 		return ;
// 	printf("=== %s ===\n", ast->token ? ast->token : "PL");
// 	printf("(L) %s | ", ast->left ? (ast->left->token ? ast->left->token : "PL") : "NULL");
// 	printf("(R) %s\n", ast->right ? (ast->right->token ? ast->right->token : "PL") : "NULL");
// 	if (ast->argc)
// 	{
// 		i = 0;
// 		printf("argv: ");
// 		while ((ast->argv)[i])
// 			printf("|%s|\t", (ast->argv)[i++]);
// 		printf("\n");
// 	}
// 	if (!ast->left && !ast->right)
// 		printf("-----------------\n");
// 	display_astree(ast->left);
// 	display_astree(ast->right);
// }

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
	if (!simplify_astree(data->astree))
		return (FALSE);
	// display_astree(data->astree);
	// printf("\n");
	return (TRUE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:13:47 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/29 18:12:35 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 나중에 삭제

void	print_env_list(void)
{
	t_env	*curr;

	curr = g_env_list;
	while (curr)
	{
		printf("key: %s | value: %s\n", curr->key, curr->value);
		curr = curr->next;
	}
}

void	print_token_list(t_data *data)
{
	t_token	*curr;

	curr = data->token_list;
	while (curr)
	{
		printf("token: %s | %d\n", curr->data, curr->is_word);
		curr = curr->next;
	}
}

void	print_astree(t_ast *ast)
{
	int	i;

	if (!ast)
		return ;
	printf("=== %s ===\n", ast->token ? ast->token : "PL");
	printf("(L) %s | ", ast->left ? (ast->left->token ? ast->left->token : "PL") : "NULL");
	printf("(R) %s\n", ast->right ? (ast->right->token ? ast->right->token : "PL") : "NULL");
	if (ast->argc)
	{
		i = 0;
		printf("argv: ");
		while ((ast->argv)[i])
			printf("|%s|\t", (ast->argv)[i++]);
		printf("\n");
	}
	if (ast->fd)
		printf("fd: %d\n", ast->fd);
	if (!ast->left && !ast->right)
		printf("-----------------\n");
	print_astree(ast->left);
	print_astree(ast->right);
}

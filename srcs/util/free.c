/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 21:23:07 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/14 21:57:49 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_list(t_data *data)
{
	t_env	*curr;
	t_env	*next;

	curr = data->env_list;
	while (curr)
	{
		next = curr->next;
		free(curr->key);
		free(curr->value);
		free(curr);
		curr = next;
	}
	data->env_list = NULL;
}

void	free_token_list(t_data *data)
{
	t_token	*curr;
	t_token	*next;

	curr = data->token_list;
	while (curr)
	{
		next = curr->next;
		free(curr->data);
		free(curr);
		curr = next;
	}
	data->token_list = NULL;
}

void	free_astree(t_ast *ast)
{
	int	i;

	if (!ast)
		return ;
	free_astree(ast->left);
	free_astree(ast->right);
	i = 0;
	while (i < ast->argc)
		free((ast->argv)[i++]);
	free(ast->argv);
	free(ast);
}

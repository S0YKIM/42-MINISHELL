/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 21:23:07 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/28 20:44:23 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_list(void)
{
	t_env	*curr;
	t_env	*next;

	curr = g_env_list;
	while (curr)
	{
		next = curr->next;
		free(curr->key);
		free(curr->value);
		free(curr);
		curr = next;
	}
	g_env_list = NULL;
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

int	free_double_pointer(char **tab)
{
	size_t	i;

	if (!tab)
		return (ERROR);
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		++i;
	}
	free(tab);
	return (ERROR);
}

void	free_display_env_list(t_env **display)
{
	t_env	*curr;
	t_env	*tmp;

	curr = *display;
	while (curr)
	{
		tmp = curr;
		curr = curr->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	*display = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 15:10:41 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/27 16:31:43 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_pl_list(t_data *data, t_ast *ast)
{
	if (!ast || ast->type < T_PL)
		return ;
	if (ast->type == T_PL)
	{
		(data->pl_list)[data->curr_pl] = ast;
		(data->curr_pl)++;
	}
	create_pl_list(data, ast->left);
	create_pl_list(data, ast->right);
}

int	execute(t_data *data)
{
	int	result;

	data->pl_list = (t_ast **)ft_calloc(data->pl_cnt, sizeof(t_ast *));
	if (!data->pl_list)
		return (FALSE);
	create_pl_list(data, data->astree);
	result = traverse_heredoc(data->astree);
	if (!result || result == ERROR)
		return (result);
	if (data->pl_cnt == 1 && data->pl_list[0]->right \
		&& exec_builtin(data->pl_list[0]->right, data))
		return (TRUE);
	data->pids = (int *)ft_calloc(data->pl_cnt, sizeof(int));
	if (!data->pids)
		return (FALSE);
	return (fork_process(data));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 15:10:41 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/25 15:43:08 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_pl_list(t_data *data, t_ast *ast)
{
	if (!ast || ast->type < T_PL)
		return ;
	create_pl_list(data, ast->right);
	create_pl_list(data, ast->left);
	if (ast->type == T_PL)
	{
		(data->pl_list)[data->curr_pl] = ast;
		(data->curr_pl)++;
	}
}

int	execute(t_data *data)
{
	int	result;

	data->pl_list = (t_ast **)ft_calloc(data->pl_cnt, sizeof(t_ast *));
	if (!data->pl_list)
		return (FALSE);
	create_pl_list(data, data->astree);
	data->curr_pl = 0;
	result = traverse_heredoc(data->astree);
	if (!result || result == ERROR)
		return (result);
	if (data->pl_cnt == 1 && exec_builtin(data->pl_list[0]->right, data))
		return (TRUE);
	return (fork_process(data));
}

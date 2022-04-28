/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:04:14 by sokim             #+#    #+#             */
/*   Updated: 2022/04/28 15:31:50 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_custom_path(t_ast *ast)
{
	char	**envp;

	envp = make_envp();
	if (!envp)
		return (FALSE);
	execve(ast->argv[0], ast->argv, envp);
	print_no_such_file(SHELL_NAME, ast->token, FALSE);
	exit(127);
}

static char	*join_path_token(char *path, char *token)
{
	char	*cmd;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	cmd = ft_strjoin(tmp, token);
	free(tmp);
	return (cmd);
}

static int	exec_reserved_path(t_ast *ast, char *path)
{
	char	*cmd;
	char	**paths;
	int		i;
	char	**envp;

	i = 0;
	paths = ft_split(path, ':');
	if (!paths)
		return (ERROR);
	envp = make_envp();
	if (!envp)
		return (free_double_pointer(paths));
	while (paths[i])
	{
		cmd = join_path_token(paths[i], ast->token);
		if (!cmd)
			return (free_double_pointer(paths));
		execve(cmd, ast->argv, envp);
		free(cmd);
		i++;
	}
	print_command_not_found(ast->token);
	exit(127);
}

void	execute_cmd(t_ast *ast, t_data *data)
{
	char	*path;
	char	*value;

	if (ft_strchr(ast->argv[0], '/'))
	{
		if (!exec_custom_path(ast))
			exit(EXIT_FAILURE);
	}
	if (exec_builtin(ast, data))
	{
		value = get_env_value("?");
		exit(ft_atol(value));
	}
	path = get_env_value("PATH");
	if (path)
	{
		if (exec_reserved_path(ast, path) == ERROR)
			exit(EXIT_FAILURE);
	}
	if (!exec_custom_path(ast))
		exit(EXIT_FAILURE);
}

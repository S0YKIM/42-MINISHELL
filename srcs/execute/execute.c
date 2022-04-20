/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:04:14 by sokim             #+#    #+#             */
/*   Updated: 2022/04/20 16:10:13 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	is_builtin(t_ast *ast)
{
	int	ret;

	ret = SUCCESS;
	if (!ft_strcmp(ast->argv[0], "cd"))
		ret = ft_cd(ast);
	else if (!ft_strcmp(ast->argv[0], "echo"))
		ret = ft_echo(ast);
	else if (!ft_strcmp(ast->argv[0], "env"))
		ret = ft_env(ast);
	else if (!ft_strcmp(ast->argv[0], "exit"))
		ft_exit(ast);
	else if (!ft_strcmp(ast->argv[0], "export"))
		ret = ft_export(ast);
	else if (!ft_strcmp(ast->argv[0], "pwd"))
		ret = ft_pwd();
	else if (!ft_strcmp(ast->argv[0], "unset"))
		ret = ft_unset(ast);
	else
		return ;
	update_env("?", ft_strdup(ft_itoa(ret)));
	exit (ret);
}

static void	exec_custom_path(t_ast *ast)
{
	update_env("?", ft_strdup("0"));
	execve(ast->argv[0], ast->argv, NULL);
	return ;
}

static void	exec_reserved_path(t_ast *ast, char *path)
{
	char	*cmd;
	char	*tmp;
	char	**paths;
	int		i;

	i = 0;
	paths = ft_split(path, ':');
	if (!paths)
		return ;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
		{
			free_double_pointer(paths);
			return ;
		}
		cmd = ft_strjoin(tmp, ast->argv[0]);
		free(tmp);
		if (!cmd)
			return ;
		execve(cmd, ast->argv, NULL);
		i++;
	}
	return ;
}

void	execute_cmd(t_ast *ast)
{
	char	*path;

	if (ft_strchr(ast->argv[0], '/'))
		exec_custom_path(ast);
	else
	{
		is_builtin(ast);
		path = get_env_value("PATH");
		if (path)
			exec_reserved_path(ast, path);
	}
	printf("microshell: %s: No such file or directory\n", ast->argv[0]);
	update_env("?", ft_strdup("127"));
	exit (127);
}

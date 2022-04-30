/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 12:19:46 by sokim             #+#    #+#             */
/*   Updated: 2022/04/30 19:34:14 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_directory(char *path, int cnt)
{
	char	*dir;

	if (!ft_strcmp(path, "~"))
		dir = get_env_value("~");
	else if (!ft_strcmp(path, "-"))
	{
		dir = get_env_value("OLDPWD");
		if (!dir)
			print_not_set("cd", "OLDPWD");
	}
	else if (cnt == 1)
	{
		dir = get_env_value("HOME");
		if (!dir)
			print_not_set("cd", "HOME");
	}
	else
		dir = ft_strdup(path);
	return (dir);
}

static int	change_directory(char *path, t_ast *ast)
{
	int		ret;
	char	*dir;

	dir = get_directory(path, ast->argc);
	if (!dir)
		return (FALSE);
	ret = chdir(dir);
	free(dir);
	if (ret == ERROR)
	{
		print_no_such_file("cd", ast->argv[1], TRUE);
		return (FALSE);
	}
	if (!ft_strcmp(path, "-"))
		printf("%s\n", path);
	return (TRUE);
}

static int	set_old_pwd(void)
{
	char	*pwd;
	int		ret;

	if (!is_there_node_with_key("OLDPWD"))
		return (TRUE);
	pwd = get_env_value("PWD");
	if (!pwd)
	{
		pwd = ft_strdup("");
		if (!pwd)
			return (FALSE);
		update_env("OLDPWD", pwd);
		return (TRUE);
	}
	ret = update_env("OLDPWD", pwd);
	if (!ret)
		return (FALSE);
	return (TRUE);
}

static int	set_pwd(char *path)
{
	char	*tmp;
	int		ret;

	if (!is_there_node_with_key("PWD"))
		return (TRUE);
	tmp = ft_strdup(path);
	if (!tmp)
		return (FALSE);
	ret = update_env("PWD", tmp);
	if (!ret)
		return (FALSE);
	return (TRUE);
}

int	ft_cd(t_ast *ast)
{
	char	path[1024];

	if (!change_directory(ast->argv[1], ast))
		return (FAILURE);
	getcwd(path, 1024);
	if (!set_old_pwd())
		return (FAILURE);
	if (!set_pwd(path))
		return (FAILURE);
	return (SUCCESS);
}

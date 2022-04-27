/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 12:19:46 by sokim             #+#    #+#             */
/*   Updated: 2022/04/28 01:35:43 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_directory(char *path)
{
	char	*dir;

	if (!ft_strcmp(path, "~"))
	{
		dir = get_env_value("HOME");
		if (!ft_strcmp(dir, ""))
		{
			print_not_set("cd", "HOME");
			return (NULL);
		}
	}
	else if (!ft_strcmp(path, "-"))
	{
		dir = get_env_value("OLDPWD");
		if (!ft_strcmp(dir, ""))
		{
			print_not_set("cd", "OLDPWD");
			return (NULL);
		}
	}
	else
		dir = ft_strdup(path);
	return (dir);
}

static int	change_directory(char *path, t_ast *ast)
{
	int		ret;
	char	*dir;

	dir = get_directory(path);
	if (!dir)
		return (FALSE);
	ret = chdir(dir);
	if (ret == ERROR)
	{
		print_no_such_file("cd", ast->argv[1], TRUE);
		return (FALSE);
	}
	return (TRUE);
}

static int	set_old_pwd(void)
{
	char	*pwd;
	int		ret;

	pwd = get_env_value("PWD");
	if (!pwd)
		return (TRUE);
	if (!is_there_node_with_key("OLDPWD"))
		return (TRUE);
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
	int		ret;
	char	path[1024];

	if (ast->argc == 1)
		return (change_directory("~", ast));
	ret = change_directory(ast->argv[1], ast);
	if (!ret)
		return (FAILURE);
	getcwd(path, 1024);
	if (!set_old_pwd())
		return (FAILURE);
	if (!set_pwd(path))
		return (FAILURE);
	return (SUCCESS);
}

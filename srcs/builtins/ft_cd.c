/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 12:19:46 by sokim             #+#    #+#             */
/*   Updated: 2022/04/19 15:03:23 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	change_directory(char *path)
{
	char	*dir;
	int		ret;

	if (*path == '~')
		dir = (get_env_value("HOME"));
	else if (*path == '-')
		dir = (get_env_value("OLDPWD"));
	else
		dir = ft_strdup(path);
	if (!dir)
		return (FALSE);
	ret = chdir(dir);
	free(dir);
	return (ret);
}

static int	set_old_pwd(void)
{
	char	*oldpwd;
	int		ret;

	oldpwd = ft_strdup("OLDPWD");
	if (!oldpwd)
		return (FALSE);
	ret = update_env(oldpwd, get_env_value("OLDPWD"));
	free(oldpwd);
	if (!ret)
		return (FALSE);
	return (TRUE);
}

static int	set_pwd(char *path)
{
	char	*pwd;
	char	*tmp;
	int		ret;

	pwd = ft_strdup("PWD");
	if (!pwd)
		return (FALSE);
	tmp = ft_strdup(path);
	if (!tmp)
	{
		free(pwd);
		return (FALSE);
	}
	ret = update_env(pwd, path);
	free(pwd);
	free(tmp);
	if (!ret)
		return (FALSE);
	return (TRUE);
}

int	ft_cd(t_ast *ast, t_data *data)
{
	int		ret;
	char	path[1024];

	if (ast->argc == 1)
		return (change_directory("~"));
	ret = change_directory(ast->argv[1]);
	if (ret == FAILURE)
	{
		printf("microshell: cd: %s: No such file or directory\n", ast->argv[1]);
		return (FAILURE);
	}
	getcwd(path, 1024);
	if (!set_old_pwd())
		return (FAILURE);
	if (!set_pwd(path))
		return (FAILURE);
	return (SUCCESS);
}

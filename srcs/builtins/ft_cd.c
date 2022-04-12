/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 12:19:46 by sokim             #+#    #+#             */
/*   Updated: 2022/04/12 23:01:24 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	change_directory(char *path, t_data *data)
{
	char	*dir;
	int		ret;

	if (!ft_strncmp(path, "~", 1))
		dir = (get_env_value_with_key(data, "HOME"));
	else if (!ft_strncmp(path, "-", 1))
		dir = (get_env_value_with_key(data, "OLDPWD"));
	else
		dir = ft_strdup(path);
	if (!dir)
		return (FAILURE);
	ret = chdir(dir);
	free(dir);
	return (ret);
}

int	ft_cd(char **cmds, t_data *data)
{
	int		ret;
	char	pwd[1024];

	if (!cmds[1])
		return (change_directory("~", data));
	ret = change_directory(cmds[1], data);
	if (ret == FAILURE)
		printf("cd: %s: No such file or directory\n", cmds[1]);
	else
	{
		getcwd(pwd, 1024);
		if (update_env(data, "OLDPWD", get_env_value_with_key(data, "PWD")) == EXIT_FAILURE)
			return (FAILURE);
		if (update_env(data, "PWD", pwd) == FAILURE)
			return (FAILURE);
	}
	return (ret);
}

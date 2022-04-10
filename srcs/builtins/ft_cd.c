/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 12:19:46 by sokim             #+#    #+#             */
/*   Updated: 2022/04/10 14:16:49 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	change_directory(char *path, t_data *data)
{
	char	*dir;
	int		ret;

	if (!ft_strncmp(path, "~", 1))
		dir = ft_strdup(get_env_value(data, "HOME"));
	else if (!ft_strncmp(path, "-", 1))
		dir = ft_strdup(get_env_value(data, "OLDPWD"));
	else
		dir = ft_strdup(path);
	if (!dir)
		return (EXIT_FAILURE);
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
	if (ret == EXIT_FAILURE)
		printf("bash: cd: %s: No such file or directory\n", cmds[1]);
	else
	{
		getcwd(pwd, 1024);
		if (update_env(data, "OLDPWD", get_env_value(data, "PWD")) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (update_env(data, "PWD", pwd) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (ret);
}

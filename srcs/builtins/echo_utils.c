/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 16:42:53 by sokim             #+#    #+#             */
/*   Updated: 2022/05/01 16:56:09 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_there_tilde(char *arg)
{
	if (!arg)
		return (FALSE);
	if (arg[0] != '~')
		return (FALSE);
	if (arg[1] && arg[1] != '/')
		return (FALSE);
	return (TRUE);
}

char	*join_home_directory(char *arg)
{
	char	*home;
	char	*ret;

	home = get_env_value("~");
	ret = ft_strjoin(home, arg + 1);
	free(home);
	return (ret);
}

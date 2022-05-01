/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 15:21:41 by sokim             #+#    #+#             */
/*   Updated: 2022/05/01 15:36:35 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_home_directory(char *path)
{
	char	*home;
	char	*ret;

	home = get_env_value("~");
	ret = ft_strjoin(home, path + 1);
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 23:38:55 by sokim             #+#    #+#             */
/*   Updated: 2022/04/13 02:49:58 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_key_name(char *key)
{
	if (!key || !key[0])
		return (FALSE);
	if (ft_isdigit(key[0]))
		return (FALSE);
	if (ft_strchr(key, '?'))
		return (FALSE);
	return (TRUE);
}

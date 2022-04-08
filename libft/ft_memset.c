/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 16:59:26 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/07 20:33:40 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*tmp;
	size_t			i;

	if (!b)
		return (0);
	tmp = (unsigned char *)b;
	i = 0;
	while (i < len)
		tmp[i++] = (unsigned char)c;
	return (b);
}

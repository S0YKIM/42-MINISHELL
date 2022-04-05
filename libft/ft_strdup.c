/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 14:45:12 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/05 19:22:11 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	size;
	char	*result;

	if (!str)
		return (NULL);
	size = ft_strlen(str) + 1;
	result = (char *)malloc(size * sizeof(char));
	if (result)
		ft_strlcpy(result, str, size);
	return (result);
}

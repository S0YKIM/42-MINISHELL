/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 16:27:45 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/11 19:04:11 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	size_t	i;
	char	*result;

	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	result = (char *)malloc(size * sizeof(char));
	if (result)
	{
		i = 0;
		while (s1 && *s1)
			result[i++] = *s1++;
		while (s2 && *s2)
			result[i++] = *s2++;
		result[i] = '\0';
	}
	return (result);
}

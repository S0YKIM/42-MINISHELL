/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:11:41 by sokim             #+#    #+#             */
/*   Updated: 2022/04/20 15:43:21 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_malloc_error(char **tab)
{
	size_t		i;

	if (!tab)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		++i;
	}
	free(tab);
	return (NULL);
}

static size_t	ft_number_of_words(char const *s, char c)
{
	size_t	cnt;
	size_t	i;

	if (!s[0])
		return (0);
	cnt = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			++cnt;
			while (s[i] && s[i] != c)
				++i;
			--i;
		}
		++i;
	}
	return (cnt);
}

static char	**split(const char *s, char c, char **tab)
{
	char const	*start;
	size_t		index;
	int			i;

	index = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			start = s + i;
			while (s[i] && s[i] != c)
				++i;
			tab[index] = (char *)malloc(sizeof(char) * (s + i - start + 1));
			if (!(tab[index]))
				return (ft_malloc_error(tab));
			ft_strlcpy(tab[index++], start, s + i - start + 1);
		}
		else
			++i;
	}
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char		**tab;

	if (!s)
		return (NULL);
	tab = (char **)ft_calloc(ft_number_of_words(s, c) + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	split(s, c, tab);
	return (tab);
}

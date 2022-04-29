/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:14:37 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/29 17:53:06 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	replace_token_substr(t_token *curr, char *key_start)
{
	char	*tmp;

	tmp = curr->data;
	curr->data = ft_substr(tmp, 0, key_start - tmp);
	free(tmp);
	if (!trim_quote(curr))
		return (FALSE);
	return (TRUE);
}

static int	replace_token(t_token *curr, char *key_start, char *str, int *i)
{
	*i = 0;
	if (curr->data != key_start)
	{
		if (!replace_token_substr(curr, key_start))
			return (FALSE);
	}
	else
	{
		free(curr->data);
		curr->data = ft_strdup(str);
		(*i)++;
	}
	if (!curr->data)
		return (FALSE);
	return (TRUE);
}

int	split_value_with_space( \
	t_token **curr, char *value, char *key_start, char *key_end)
{
	char	**arr;
	int		i;
	int		len;

	if (*(key_end + 1) && !insert_token_node(curr, ft_strdup(key_end + 1)))
		return (ERROR);
	arr = ft_split(value, ' ');
	free(value);
	if (!arr)
		return (ERROR);
	if (!replace_token(*curr, key_start, arr[0], &i))
		return (ERROR);
	while (arr[i])
	{
		if (!insert_token_node(curr, ft_strdup(arr[i++])))
			return (ERROR);
		*curr = (*curr)->next;
	}
	len = ft_strlen(arr[i - 1]);
	free_double_pointer(arr);
	return (len);
}

int	handle_invalid_env(t_token **curr, char *value, char *key_start)
{
	free(value);
	if ((*curr)->data != key_start)
	{
		if (!replace_token_substr(*curr, key_start))
			return (ERROR);
		if (!insert_token_node(curr, ft_strdup("")))
			return (FALSE);
		*curr = (*curr)->next;
	}
	return (REMOVE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 22:36:12 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/12 17:22:49 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_value(t_data *data, char **start, char **ks, char **ke)
{
	char	*key;
	char	*value;

	*ks = ft_strchr(*start + 1, '$');
	if (!*ks)
		return (NULL);
	(*ks)++;
	*ke = *ks;
	while (**ke)
	{
		if (!*(*ke + 1) || *(*ke + 1) == '\'' || *(*ke + 1) == '\"')
			break ;
		(*ke)++;
	}
	key = ft_substr(*ks, 0, *ke - *ks + 1);
	if (!key)
		return (NULL);
	value = get_env_value(data, key);
	free(key);
	return (value);
}

static char	*expand_new_token(t_data *data, t_token *curr, char **start)
{
	char	*value;
	char	*key_start;
	char	*key_end;
	char	*head;
	char	*new_token;

	value = expand_value(data, start, &key_start, &key_end);
	if (!value)
		return (NULL);
	*(key_start - 1) = '\0';
	head = ft_strjoin(curr->data, value);
	free(value);
	if (!head)
		return (NULL);
	new_token = ft_strjoin(head, key_end + 1);
	free(head);
	return (new_token);
}

int	expand_env(t_data *data, t_token *curr, char **start, char **end)
{
	int		len;
	char	*new_token;

	new_token = expand_new_token(data, curr, start);
	if (!new_token)
		return (ERROR);
	free(curr->data);
	curr->data = new_token;
	len = 0;
	*start = find_quote(curr->data, &len);
	*end = ft_strchr(*start + 1, **start);
	return (len);
}

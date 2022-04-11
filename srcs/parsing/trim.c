/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 21:40:15 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/11 21:51:13 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	trim_quote(t_token *curr, char *start, char *end, int *len)
{
	char	*head;
	char	*new_token;

	if (*start == '\'')
		curr->no_expand = TRUE;
	*start = '\0';
	*end = '\0';
	*len += ft_strlen(start + 1);
	head = ft_strjoin(curr->data, start + 1);
	if (!head)
		return (FALSE);
	new_token = ft_strjoin(head, end + 1);
	free(head);
	if (!new_token)
		return (FALSE);
	free(curr->data);
	curr->data = new_token;
	return (TRUE);
}

static char	*find_quote(char *str, int *len)
{
	while (*str && *str != '\"' && *str != '\'')
	{
		str++;
		(*len)++;
	}
	return (str);
}

int	trim_token(t_data *data)
{
	t_token	*curr;
	char	*start;
	char	*end;
	int		len;

	curr = data->token_list;
	while (curr)
	{
		len = 0;
		start = curr->data;
		while (*start)
		{
			start = find_quote(start, &len);
			if (!*start)
				break ;
			end = ft_strchr(start + 1, *start);
			if (!end)
				break ;
			if (!trim_quote(curr, start, end, &len))
				return (FALSE);
			start = curr->data + len;
		}
		curr = curr->next;
	}
	return (TRUE);
}

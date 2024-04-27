/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token_valid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 21:13:29 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/27 16:54:40 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in_quote_tokens(t_token *token)
{
	t_token	*head;
	char	quote;
	int		n;
	int		is_in_quote;

	quote = '\'';
	n = -1;
	while (++n < 2)
	{
		head = token->prev;
		is_in_quote = 0;
		while (head && *token->value != quote)
		{
			if (*head->value == quote && !is_in_quote_tokens(head))
				is_in_quote = !is_in_quote;
			head = head->prev;
		}
		if (is_in_quote)
			return (1);
		quote = '\"';
	}
	return (0);
}

int	is_valid_multi_meta(t_token *token) // validates consecutive metachar
{
	char	*value;

	value = token->value;
	if (ft_strchr("|&<>", *value))
	{
		
	}
	return (1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token_valid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 21:13:29 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/29 22:49:50 by zyeoh            ###   ########.fr       */
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

int	is_valid_multi_operand(t_token *token) // validates consecutive metachar
{
	if (!token || !token->prev || token->type == SPACE)
		return (1);
	if (2 < token->prev->type && token->prev->type < 10)
	{
		output_token_error(token->value);
		return (0);
	}
	return (1);
}

int	is_valid_redir_file(t_token *token)
{
	if (!token || !is_file_token(token))
		return (1);
	if (2 < token->type && token->type < 12)
	{
		output_token_error(token->value);
		return (0);
	}
	return (1);
}
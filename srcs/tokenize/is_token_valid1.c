/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token_valid1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 21:13:29 by zyeoh             #+#    #+#             */
/*   Updated: 2024/08/22 13:04:01 by zyeoh            ###   ########.fr       */
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

// validates consecutive metachar
int	is_valid_multi_operand(t_token *token)
{
	t_token	*head;

	if (!token || !token->prev || token->type == WHITESPACE)
		return (1);
	if (token->type == OPEN_PARENT || token->type == CLOSED_PARENT)
		return (1);
	head = token->prev;
	while (head && head->type == WHITESPACE)
		head = head->prev;
	if (!head)
		return (1);
	if (2 < token->type && token->type < 7)
	{
		if (2 < head->type && head->type < 7)
		{
			output_token_error(token->value);
			return (0);
		}
	}
	else if (1 < head->type && head->type < 10)
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

// checks for fd redirect
int	is_valid_edgecase_digit_redir(t_token *token)
{
	int	n;

	if (!token || !token->next)
		return (1);
	n = -1;
	while (token->value[++n])
	{
		if (!ft_isdigit(token->value[n]))
			return (1);
	}
	if (REDIR_OUT <= token->next->type && token->next->type <= REDIR_HEREDOC)
	{
		if (ft_atol(token->value) > INT_MAX || ft_strlen(token->value) > 10)
			output_token_error("-1");
		else
			output_token_error(token->value);
		return (0);
	}
	return (1);
}

// checks if it is a hanging close parenthesis
int	is_valid_closed_parenthesis(t_token *token)
{
	int	closed_count;

	if (!token || token->type != CLOSED_PARENT)
		return (1);
	if (!token->prev)
	{
		output_token_error(")");
		return (0);
	}
	token = token->prev;
	closed_count = 1;
	while (token && closed_count > 0)
	{
		if (token->type == OPEN_PARENT)
			closed_count--;
		else if (token->type == CLOSED_PARENT)
			closed_count++;
		token = token->prev;
	}
	if (closed_count > 0)
	{
		output_token_error(")");
		return (0);
	}
	return (1);
}

// int	is_valid_open_parenthesis(t_token *token)
// {
// 	int open_count;

// 	if (!token || token->type != CLOSED_PARENT)
// 		return (1);
// 	if (!token->prev)
// 		return (0);
// 	token = token->prev;
// 	closed_count = 1;
// 	while (token && closed_count > 0)
// 	{
// 		if (token->type == OPEN_PARENT)
// 			closed_count--;
// 		else if (token->type == CLOSED_PARENT)
// 			closed_count++;
// 		token = token->prev;
// 	}
// 	if (closed_count > 0)
// 	{
// 		output_token_error(")");
// 		return (0);
// 	}
// 	return (1);
// }

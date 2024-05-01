/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token_valid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Zyeoh <yeohzishen2002@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 21:13:29 by zyeoh             #+#    #+#             */
/*   Updated: 2024/05/01 01:22:30 by Zyeoh            ###   ########.fr       */
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
	t_token *head;
	
	if (!token || !token->prev || token->type == WHITESPACE)
		return (1);
	head = token->prev;
	while (head && head->type == WHITESPACE)
		head = head->prev;
	if (0 < head->type && head->type < 7)
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

int	is_valid_edgecase_digit_redir(t_token *token) //checks for fd redirect
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

int	is_valid_closed_parenthesis(t_token *token) // checkss if it is a hanging close parenthesis
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

int	is_valid_parenthesis_content(t_token *token) //checks if there is a WORD in the parentheses
{
	if (!token || token->type != CLOSED_PARENT)
		return (1);
	if (!token->prev)
	{
		output_token_error(")");
		return (0);
	}
	token = token->prev;
	while (token && token->type != OPEN_PARENT)
	{
		if (token->type == CLOSED_PARENT || token->type == WORDS)
			return (1);
		token = token->prev;
	}
	output_token_error(")");
	return (0);
}

int	is_valid_parenthesis_position(t_token *token) //checks if it is not the first thing in it's simple command
{
	if (!token || token->type != OPEN_PARENT || !token->prev)
		return (1);
	token = token->prev;
	while (token && token->type == WHITESPACE)
		token = token->prev;
	if (token->type == WORDS || (REDIR_OUT <= token->type
			&& token->type <= REDIR_HEREDOC) || token->type == CLOSED_PARENT)
	{
		output_token_error("(");
		return (0);
	}
	return (1);
}

int	is_valid_operand_content(t_token *token) // checks for |, || and && if they have WORDS before
{
	t_token	*head;

	if (!token || !(PIPE <= token->type && token->type <= OR))
		return (1);
	head = token->prev;
	while (head && head->type == WHITESPACE)
		head = head->prev;
	if (!head || head->type != WORDS)
	{
		output_token_error(token->value);
		return (0);
	}
	return (1);
}

int is_valid_special_character(t_token *token)
{
	if (!token)
		return (1);
	if (token->type == AMPERSAND)
	{
		output_token_error(token->value);
		return (0);
	}
	return (1);
}

int is_valid_last_token(t_token *token)
{
	t_token *head;
	
	if (!token && token->type == WHITESPACE)
		return (1);
	head = token->next;
	while (head && head->type == WHITESPACE)
		head = head->next;
	if (!head)
	{
		if (REDIR_OUT <= token->type && token->type <= REDIR_HEREDOC)
		{
			output_token_error("newline");
			return (0);
		}
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

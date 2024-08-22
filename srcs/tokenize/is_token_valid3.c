/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token_valid3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:55:45 by zyeoh             #+#    #+#             */
/*   Updated: 2024/08/22 10:56:38 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// checks if there is a WORD in the parentheses
int	is_valid_parenthesis_content(t_token *token)
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
		if (2 < token->type && token->type < 10)
			break ;
		if (token->type == CLOSED_PARENT || token->type == WORDS)
			return (1);
		token = token->prev;
	}
	output_token_error(")");
	return (0);
}

// checks if it is not the first thing in it's simple command
int	is_valid_parenthesis_position(t_token *token)
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

// checks for |, || and && if they have WORDS before
int	is_valid_operand_content(t_token *token)
{
	t_token	*head;

	if (!token || !(PIPES <= token->type && token->type <= OR))
		return (1);
	head = token->prev;
	while (head && head->type == WHITESPACE)
		head = head->prev;
	if (!head || head->type == OPEN_PARENT)
	{
		output_token_error(token->value);
		return (0);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token_valid2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:55:22 by zyeoh             #+#    #+#             */
/*   Updated: 2024/08/22 10:55:30 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_special_character(t_token *token)
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

int	is_valid_last_token(t_token *token)
{
	t_token	*head;

	if (!token || token->type == WHITESPACE)
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

int	is_valid_edgecase_limiter(t_token *token)
{
	t_token	*head;

	if (!token || !token->prev)
		return (1);
	head = token->prev;
	while (head && head->type == WHITESPACE)
		head = head->prev;
	if (head && head->type == REDIR_HEREDOC)
	{
		if (token->type == WORDS && token->open_end == 1)
		{
			output_token_error(token->value);
			return (0);
		}
	}
	return (1);
}

int	is_banned_character(t_token *token)
{
	if (!token)
		return (1);
	if (token->type == TOKEN_FAIL)
	{
		output_token_error(token->value);
		return (0);
	}
	return (1);
}

int	is_valid_subshell_argument(t_token *token)
{
	t_token	*head;

	if (!token || !token->prev || token->type == WHITESPACE)
		return (1);
	if (token->type != WORDS || is_file_token(token))
		return (1);
	head = token->prev;
	while (head && head->type < 7)
		head = head->prev;
	if (head && head->type == CLOSED_PARENT)
	{
		if (head && head->type == CLOSED_PARENT)
		{
			output_token_error(token->value);
			return (0);
		}
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token_valid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Zyeoh <yeohzishen2002@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 21:13:29 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/30 14:02:17 by Zyeoh            ###   ########.fr       */
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

int	is_valid_closed_parenthesis(t_token *token)
{
	int closed_count;

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

int is_valid_parenthesis_content(t_token *token)
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

int is_valid_parenthesis_position(t_token *token)
{
	if (!token || token->type != OPEN_PARENT || !token->prev)
		return (1);
	token = token->prev;
	while(token)
	{
		if (token->type == WORDS || (REDIR_OUT <= token->type && token->type <= REDIR_HEREDOC))
		{
			output_token_error("(");
			return (0);
		}
		token = token->prev;
	}
	return (1);
}

int is_valid_operand_position(t_token *token)
{
	t_token *head;
	
	if (!token || !(PIPE <= token->type && token->type <= OR))
		return (1);
	head = token->prev;
	while (head && head->type == SPACE)
		head = head->prev;
	if (!head)
	{
		output_token_error(token->value);
		return (0);
	}
	return(1);
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

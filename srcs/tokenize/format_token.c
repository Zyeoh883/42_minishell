/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:56:12 by zyeoh             #+#    #+#             */
/*   Updated: 2024/05/20 21:42:24 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	format_quotes(t_token *token)
{
	char	quote;

	while (token)
	{
		while (token->open_end == 1)
		{
			token_combine_wnext(token);
			if (token->value[0] == token->value[ft_strlen(token->value) - 1]
				&& ft_strlen(token->value) > 1)
			{
				token->open_end = 0;
				token = token->next;
			}
		}
		if (token && ft_strchr("'\"", *token->value))
		{
			quote = *token->value;
			while (token->next && *token->next->value != quote)
				token_combine_wnext(token);
			if (!token->next)
				token->open_end = 1;
			token_combine_wnext(token);
		}
		token = token->next;
	}
}

void	format_whitespace(t_token *token)
{
	while (token && token->next)
	{
		if (token->type == WHITESPACE)
		{
			while (token->next && token->next->type == WHITESPACE)
				token_remove(token->next);
		}
		token = token->next;
	}
}

void	label_tokens(t_token *token)
{
	while (token)
	{
		if (is_operand(*token->value) && ft_strlen(token->value) == 1)
		{
			if (*token->value == '>')
				token->type = REDIR_OUT;
			else if (*token->value == '<')
				token->type = REDIR_IN;
			else if (*token->value == '|')
				token->type = PIPE;
			else if (*token->value == '&')
				token->type = AMPERSAND;
			else if (*token->value == ' ')
				token->type = WHITESPACE;
			else if (*token->value == '(')
				token->type = OPEN_PARENT;
			else if (*token->value == ')')
				token->type = CLOSED_PARENT;
		}
		token = token->next;
	}
}

void	format_operands(t_token *token)
{
	while (token && token->next)
	{
		if (WHITESPACE < token->type && token->type < AND)
		{
			if (token->type == token->next->type)
			{
				token_combine_wnext(token);
				if (token->type == REDIR_OUT)
					token->type = REDIR_APPEND;
				else if (token->type == REDIR_IN)
					token->type = REDIR_HEREDOC;
				else if (token->type == PIPE)
					token->type = OR;
				else if (token->type == AMPERSAND)
					token->type = AND;
			}
			else if (token->type == REDIR_OUT && token->next->type == PIPE)
				token_combine_wnext(token);
		}
		token = token->next;
	}
}

void	format_tokens(t_token *token_root)
{
	t_token	*token;

	token = token_root;
	format_quotes(token);
	label_tokens(token);
	format_whitespace(token);
	format_operands(token);
}

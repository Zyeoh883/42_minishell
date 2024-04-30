/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:56:12 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/30 16:51:44 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	format_quotes(t_token *token)
{
	char	quote;

	while (token)
	{
		if (ft_strchr("'\"", *token->value))
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
		if (token->type == SPACE)
		{
			while (token->next && token->next->type == SPACE)
				token_remove(token->next);
		}
		token = token->next;
	}
}

void	label_tokens(t_token *token)
{
	while (token)
	{
		if (is_operand(*token->value))
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
				token->type = SPACE;
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
		if (1 < token->type && token->type < 8)
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

// format_parenthesis(token); // TODO figure when to call this,

// void format_parenthesis(t_token *token)  // TODO Fix order of enclosure
// {
// 	while (token)
// 	{
// 		if (*token->value == '(')
// 		{
// 			while (token->next
// && *token->next->value != ')'&& *token->next->value != '(')
// 				token_combine_wnext(token);
// 			if (!token->next)
// 				token->open_end = 1;
// 			token_combine_wnext(token);
// 		}
// 		token = token->next;
// 	}
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Zyeoh <yeohzishen2002@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:23:50 by zyeoh             #+#    #+#             */
/*   Updated: 2024/05/31 23:18:09 by Zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_file_token(t_token *token)
{
    if (token && token->type == WHITESPACE)
		return (0);
	token = token->prev;
	while (token && token->type == WHITESPACE)
		token = token->prev;
	if (token && REDIR_OUT <= token->type && token->type <= REDIR_HEREDOC)
		return (1);
	return (0);
}

int is_in_parentheses(t_token *token)
{
    int count_parentheses;

    if (!token || !token->prev)
        return (0);
    count_parentheses = 0;
    token = token->prev;
    while (token)
    {
		if (token->type == CLOSED_PARENT)
			count_parentheses--;
        else if (token->type == OPEN_PARENT)
            count_parentheses++;
        if (count_parentheses > 0)
			return (1);
        token = token->prev;
    }
    return (0);
}

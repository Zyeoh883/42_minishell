/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:23:50 by zyeoh             #+#    #+#             */
/*   Updated: 2024/05/27 17:53:07 by zyeoh            ###   ########.fr       */
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

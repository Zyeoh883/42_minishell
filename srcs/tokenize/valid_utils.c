/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 21:13:29 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/25 01:22:16 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in_quote_tokens(t_token *root_token, t_token *token)
{
	t_token	*head;
	char	quote;
	int		n;
	int		is_in_quote;

	quote = '\'';
	n = -1;
	while (++n < 2)
	{
		head = root_token;
		is_in_quote = 0;
		while (*token->value != quote && head && head != token)
		{
			if (*head->value == quote && !is_in_quote_tokens(root_token, head))
				is_in_quote = !is_in_quote;
			head = head->next;
		}
		if (is_in_quote)
			return (1);
		quote = '\"';
	}
	return (0);
}

// int validate_tokens(t_node *root_token)
// {

// }
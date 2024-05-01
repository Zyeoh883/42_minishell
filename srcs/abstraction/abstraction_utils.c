/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abstraction_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Zyeoh <yeohzishen2002@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 12:30:07 by Zyeoh             #+#    #+#             */
/*   Updated: 2024/05/01 12:40:11 by Zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_in_parentheses(t_token *token)
{
    int count_parentheses;

    if (!token || !token->prev)
        return (0);
    count_parentheses = 0;
    token = token->prev;
    while (token)
    {
        if (count_parentheses > 0)
			return (1);
		if (token->type == CLOSED_PARENT)
			count_parenthe
    }
}
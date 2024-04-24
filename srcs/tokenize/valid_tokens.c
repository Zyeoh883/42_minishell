/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 01:24:41 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/25 02:26:41 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int valid_file_b4_redir(t_token *token)
{
    if (!token)
        return (0);
    
}

int	is_redirections_valid(t_token *root_token)
{
	t_token *head;
    t_token *temp;

    head = last_token_nonspace(root_token);
    if (ft_strchr("><", *head->value) && !is_in_quote_tokens(root_token, head)) // checks hanging redirect
    {
        // TODO free nodes and values
        output_token_error("newline");
        exit(TOKEN_FAIL);
    }
	head = root_token;
	while (head)
	{
		if (ft_strchr("><", *head->value) && !is_in_quote_tokens(root_token, // check if file is allnum and node.next is not redirect
				head))
		{
            temp = head->next;
		}
		head = head->next;
	}
}

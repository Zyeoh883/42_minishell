/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 01:24:41 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/27 21:22:07 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_isvalid_function_array(int is_meta,
		int (*isvalid_function_array[7])(t_token *)) // TODO complete is_valid functions
{
	if (is_meta)
	{
		isvalid_function_array[0] = is_in_quote_tokens;
		// isvalid_function_array[1] = is_metacharacter;
		isvalid_function_array[1] = NULL;
	}
	else
	{
		
	}
}

int	is_valid_token(t_token *token) // TODO test this more
{
	int (*isvalid_function_array[7])(t_token *);
	int is_meta;
	int n;

	if (!token || is_in_quote_tokens(token) || *token->value != ' ')	// end of tokens, is in quotes, is a whitespace == valid
		return (1);
	is_meta = is_metacharacter(*token->value);
	set_isvalid_function_array(is_meta, isvalid_function_array);
	n = -1;
	while (isvalid_function_array[++n])
	{
		if (!isvalid_function_array[n](token))
			return (0);
	}
	return (1);
}

// if (is_metacharacter(*token->value))
// 	{
// 		// check for triple operator
// 		// several check per operator
// 	}
// 	else
// 	{
// 		// check if all values all characters are valid + !is_in_quotes
// 		// check if is redirected, is all num and .next is redirect
// 	}

// int valid_file_b4_redir(t_token *token) // TODO complete this
// {
//     if (!token)
//         return (0);

// }

// int	is_redirections_valid(t_token *root_token)
// {
// 	t_token *head;
//     t_token *temp;

//     head = last_token_nonspace(root_token);
//     if (ft_strchr("><", *head->value) && !is_in_quote_tokens(root_token,
// head)) // checks hanging redirect
//     {
//         // TODO free nodes and values
//         output_token_error("newline");
//         exit(TOKEN_FAIL);
//     }
// 	head = root_token;
// 	while (head)
// 	{
// 		if (ft_strchr("><", *head->value) && !is_in_quote_tokens(root_token,
// check if file is allnum and node.next is not redirect
// 				head))
// 		{
//             temp = head->next; // TODO complete this

// 		}
// 		head = head->next;
// 	}
// }

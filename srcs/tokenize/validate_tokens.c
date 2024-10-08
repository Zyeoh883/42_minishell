/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 01:24:41 by zyeoh             #+#    #+#             */
/*   Updated: 2024/08/22 12:28:45 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_isvalid_function_array(int is_meta,
		int (*isvalid_function_array[10])(t_token *))
{
	ft_bzero(isvalid_function_array, sizeof(int *) * 10);
	isvalid_function_array[0] = is_valid_redir_file;
	if (is_meta)
	{
		isvalid_function_array[1] = is_valid_multi_operand;
		isvalid_function_array[2] = is_valid_closed_parenthesis;
		isvalid_function_array[3] = is_valid_parenthesis_content;
		isvalid_function_array[4] = is_valid_parenthesis_position;
		isvalid_function_array[5] = is_valid_operand_content;
		isvalid_function_array[6] = is_valid_special_character;
		isvalid_function_array[7] = is_valid_last_token;
		isvalid_function_array[8] = is_banned_character;
	}
	else
	{
		isvalid_function_array[1] = is_valid_edgecase_digit_redir;
		isvalid_function_array[2] = is_valid_edgecase_limiter;
		isvalid_function_array[3] = is_valid_subshell_argument;
	}
}

int	is_valid_token(t_token *token)
{
	int	(*isvalid_function_array[10])(t_token *);
	int	is_meta;
	int	n;

	if (!token)
		return (1);
	is_meta = (0 < token->type);
	set_isvalid_function_array(is_meta, isvalid_function_array);
	n = -1;
	while (isvalid_function_array[++n])
	{
		if (!isvalid_function_array[n](token))
		{
			return (0);
		}
	}
	return (1);
}
			// printf("is_meta %d failed at function %d\n", is_meta, n);
			// print_tokens(token);

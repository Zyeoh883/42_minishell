/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 01:24:41 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/30 01:18:58 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_isvalid_function_array(int is_meta,
		int (*isvalid_function_array[7])(t_token *))
		// TODO complete is_valid functions
{
	ft_bzero(isvalid_function_array, sizeof(int *) * 7);
	isvalid_function_array[0] = is_valid_redir_file;
	if (is_meta)
	{
		isvalid_function_array[1] = is_valid_multi_operand;
		isvalid_function_array[2] = is_valid_closed_parenthesis;
	}
	else
	{
		isvalid_function_array[1] = is_valid_edgecase_digit_redir;
	}
}

int	is_valid_token(t_token *token) // TODO test this more
{
	int (*isvalid_function_array[7])(t_token *);
	int is_meta;
	int n;

	if (!token || token->open_end == 1)
		return (1);
	is_meta = (0 < token->type);
	set_isvalid_function_array(is_meta, isvalid_function_array);
	n = -1;
	while (isvalid_function_array[++n])
	{
		if (!isvalid_function_array[n](token))
		{
			printf("is_meta %d failed at fucntion %d\n", is_meta, n);
			return (0);
		}
	}
	return (1);
}

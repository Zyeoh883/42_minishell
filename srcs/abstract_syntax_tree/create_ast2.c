/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:05:17 by zyeoh             #+#    #+#             */
/*   Updated: 2024/08/22 11:05:24 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*create_node(t_data *shell_data, t_token *token)
{
	if (token_instances(token, is_and_or) > 0)
	{
		return (create_and_or(shell_data, token));
	}
	else if (token_instances(token, is_pipe_token) > 0)
	{
		return (create_pipe(shell_data, token));
	}
	else if (is_subshell(token))
	{
		return (create_subshell(shell_data, token));
	}
	return (create_simple_command(shell_data, token));
}

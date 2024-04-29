/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:23:50 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/29 22:37:24 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_file_token(t_token *token)
{
	token = token->prev;
	while (token && token->type == SPACE)
		token = token->prev;
	printf("test1\n");
	if (token && REDIR_OUT <= token->type && token->type <= REDIR_HEREDOC)
		return (1);
	printf("test2\n");
	return (0);
}

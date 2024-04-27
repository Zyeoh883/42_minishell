/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:56:12 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/27 21:39:04 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	format_tokens(t_token *token_root)
{
	t_token	*token;

	token = token_root;
	token_combine_wnext(token_root->next->next);
	token_combine_wnext(token_root->next->next);
	printf("\n\n");
}
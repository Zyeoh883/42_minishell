/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_asterisk.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:01:51 by sting             #+#    #+#             */
/*   Updated: 2024/07/18 16:20:22 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	combine_non_asterisk_tokens(t_token *token)
{
	while (token && token->next)
	{
		if ((token->type == QUOTED || token->value[0] != '*')
			&& (token->next->type == QUOTED || (token->next)->value[0] != '*'))
			token_combine_wnext(token);
		else
			token = token->next;
	}
}

// returns next token for while loop
t_token	*replace_token_with_separated_lst(t_token **token_root, t_token *cur,
		t_token *separated_lst)
{
	t_token	*next;

	next = cur->next;
	if (cur->prev)
	{
		(cur->prev)->next = separated_lst;
		separated_lst->prev = cur->prev;
	}
	else
		*token_root = separated_lst;
	if (next)
		next->prev = token_last(separated_lst);
	token_last(separated_lst)->next = next;
	cur->next = NULL;
	free_tokens(cur);
	return (next);
}

t_token	*separate_non_asterisk_from_asterisk_chars(char *str)
{
	t_token	*separated_lst;
	char	*start;

	separated_lst = NULL;
	while (*str)
	{
		start = str;
		if (*str == '*')
			while (*str && *str == '*')
				str++;
		else
			while (*str && *str != '*')
				str++;
		token_add_back(&separated_lst, str_to_token(start, str - start));
	}
	return (separated_lst);
}

/*
token(Before): | hi***hi |
token(After):  | hi | *** | hi |
*/
void	tokenize_asterisks(t_token **token_root)
{
	t_token	*cur;
	t_token	*separated_lst;

	cur = *token_root;
	while (cur)
	{
		if (cur->type == QUOTED)
		{
			cur = cur->next;
			continue ;
		}
		separated_lst = separate_non_asterisk_from_asterisk_chars(cur->value);
		cur = replace_token_with_separated_lst(token_root, cur, separated_lst);
	}
}

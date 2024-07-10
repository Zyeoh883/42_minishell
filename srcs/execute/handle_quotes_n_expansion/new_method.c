/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_method.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:31:51 by sting             #+#    #+#             */
/*   Updated: 2024/07/10 14:55:17 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_var_for_all_tokens(t_token *token, t_var *var_lst, int *do_ft_split)
{
	int	expand;

	while (token)
	{
		if (!is_str_quoted(token->value) && ft_strchr(token->value, '$'))
			*do_ft_split = true;
		expand = ON;
		if (token->value[0] == '\'')
			expand = OFF;
		if (expand == ON && ft_strchr(token->value, '$') != NULL)
			expand_str(&token->value, var_lst);
		token = token->next;
	}
}

void expand_var(char **str_add, t_var *var_lst, int *do_ft_split)
{
	t_token	*token_root;

	token_root = tokenize_metacharacters(*str_add);
	format_quotes(token_root);
	trim_quotes_n_expand_for_all_tokens(token_root, var_lst, do_ft_split);
	free(*str_add);
	*str_add = concatenate_all_str_in_token_lst(token_root);
	free_tokens(token_root);
}

// TODO: change name so that this func is just trim_quotes()
void	trim_quotes_for_all_tokens(t_token *token)
{
	char	*trimmed_str;

	while (token)
	{
		if (is_str_quoted(token->value))
		{
			trimmed_str = ft_substr(token->value, 1, ft_strlen(token->value) - 2);
			free(token->value);
			token->value = trimmed_str;
		}
		token = token->next;
	}
}

void trim_quotes(char **str_add)
{
	t_token	*token_root;
	
	token_root = tokenize_metacharacters(*str_add);
	format_quotes(token_root);
	trim_quotes_for_all_tokens(token_root);
	free(*str_add);
	*str_add = concatenate_all_str_in_token_lst(token_root);
	free_tokens(token_root);
}
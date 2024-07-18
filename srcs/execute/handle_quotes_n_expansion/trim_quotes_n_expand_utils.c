/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes_n_expand_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:57:53 by sting             #+#    #+#             */
/*   Updated: 2024/07/18 13:59:39 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_str_quoted(char *str)
{
	if (str[0] == '\'' || str[0] == '\"')
		return (true);
	return (false);
}

void	trim_quotes_n_expand_for_all_tokens(t_token *token, t_var *var_lst,
		int *do_ft_split)
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
		if (is_str_quoted(token->value))
			token->type = QUOTED;
		token = token->next;
	}
}

char	*join_all_str_in_token_lst(t_token *token)
{
	char	*combined_str;

	while (token && token->next)
		token_combine_wnext(token);
	combined_str = ft_strdup_w_check(token->value);
	return (combined_str);
}

void	expand_var(char **str_add, t_var *var_lst, int *do_ft_split)
{
	t_token	*token_root;

	token_root = tokenize_metacharacters(*str_add);
	format_quotes(token_root);
	trim_quotes_n_expand_for_all_tokens(token_root, var_lst, do_ft_split);
	free(*str_add);
	*str_add = join_all_str_in_token_lst(token_root);
	free_tokens(token_root);
}

// labels token->type == QUOTED
void	trim_quotes_for_all_tokens(t_token *token)
{
	char	*trimmed_str;

	while (token)
	{
		if (is_str_quoted(token->value))
		{
			token->type = QUOTED;
			trimmed_str = ft_substr(token->value, 1, ft_strlen(token->value)
					- 2);
			free(token->value);
			token->value = trimmed_str;
		}
		token = token->next;
	}
}

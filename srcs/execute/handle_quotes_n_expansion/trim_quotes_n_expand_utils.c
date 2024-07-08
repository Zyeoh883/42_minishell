/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes_n_expand_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:57:53 by sting             #+#    #+#             */
/*   Updated: 2024/07/08 14:11:45 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_str_quoted(char *str)
{
	if (str[0] == '\'' || str[0] == '\"')
		return (true);
	return (false);
}

void	trim_quotes(char **str_add)
{
	char	*trimmed_str;

	trimmed_str = ft_substr(*str_add, 1, ft_strlen(*str_add) - 2);
	free(*str_add);
	*str_add = trimmed_str;
}

void	trim_quotes_n_expand_for_all_tokens(t_token *token, t_var *var_lst, int *do_ft_split)
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
		{
			trim_quotes(&token->value);
			token->type = QUOTED;
		}
		token = token->next;
	}
}

char	*concatenate_all_str_in_token_lst(t_token *token)
{
	char	*combined_str;

	while (token && token->next)
		token_combine_wnext(token);
	combined_str = ft_strdup(token->value);
	if_null_perror_n_exit(combined_str, "ft_strdup", EXIT_FAILURE);
	return (combined_str);
}

// void	trim_quotes_n_expand_str(char **str_add, t_var *var_lst, int *do_ft_split)
// {
// 	t_token	*token_root;

// 	token_root = tokenize_metacharacters(*str_add);
// 	format_quotes(token_root);
// 	trim_quotes_n_expand_for_all_tokens(token_root, var_lst, do_ft_split);
// 	free(*str_add);
// 	*str_add = concatenate_all_str_in_token_lst(token_root);
// 	free(token_root);
// }

// * new method
void	trim_quotes_n_expand_str(char **str_add, t_var *var_lst, t_token *token, int *do_ft_split)
{
	trim_quotes_n_expand_for_all_tokens(token, var_lst, do_ft_split);
	free(*str_add);
	*str_add = concatenate_all_str_in_token_lst(token);
}

void	remove_empty_arg(char ***cmd_arg, int index)
{
	int		i;
	int		j;
	char	**new_arr;
	char	**arr;

	arr = *cmd_arg;
	new_arr = (char **)ft_calloc((arr_str_count(arr) - 1) + 1, sizeof(char *));
	if_null_perror_n_exit(new_arr, "ft_calloc", EXIT_FAILURE);
	i = -1;
	j = 0;
	while (arr[++i])
	{
		if (i == index)
			continue ;
		copy_str_to_arr(new_arr, j, arr[i]);
		j++;
	}
	free_str_arr(*cmd_arg);
	*cmd_arg = new_arr;
}

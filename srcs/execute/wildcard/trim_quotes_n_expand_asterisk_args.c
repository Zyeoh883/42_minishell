/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes_n_expand_asterisk_args.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:56:33 by sting             #+#    #+#             */
/*   Updated: 2024/07/18 11:27:05 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_arg_w_token_lst(char ***cmd_arg, int *index,
		t_token *token_root)
{
	free((*cmd_arg)[*index]);
	(*cmd_arg)[*index] = join_all_str_in_token_lst(token_root);
}

int	handle_asterisk_expansion_arg(char ***cmd_arg, int *index,
		t_token *token_root)
{
	t_list	*entry_lst;
	t_list	*expanded_lst;

	if (get_directory_entries(&entry_lst) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	expanded_lst = gather_matching_entries(entry_lst, token_root);
	if (ft_lstsize(expanded_lst) != 0)
	{
		replace_arg_w_expanded_lst(cmd_arg, *index, expanded_lst);
		*index = *index - 1 + ft_lstsize(expanded_lst);
	}
	else
		replace_arg_w_token_lst(cmd_arg, index, token_root);
	(free_lst(expanded_lst), free_lst(entry_lst));
	return (EXIT_SUCCESS);
}

// returns new_index after expanding wildcard
int	trim_quotes_n_expand_asterisk_args(char ***cmd_arg, int *index)
{
	t_token	*token_root;
	int		res;

	token_root = tokenize_metacharacters((*cmd_arg)[*index]);
	format_quotes(token_root);
	trim_quotes_for_all_tokens(token_root);
	tokenize_asterisks(&token_root);
	combine_non_asterisk_tokens(token_root);
	if (does_valid_asterisk_exist(token_root) == true)
	{
		res = handle_asterisk_expansion_arg(cmd_arg, index, token_root);
		free_tokens(token_root);
		return (res);
	}
	replace_arg_w_token_lst(cmd_arg, index, token_root);
	free_tokens(token_root);
	return (EXIT_SUCCESS);
}

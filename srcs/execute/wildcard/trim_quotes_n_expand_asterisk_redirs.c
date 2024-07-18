/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes_n_expand_asterisk_redirs.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:56:33 by sting             #+#    #+#             */
/*   Updated: 2024/07/18 11:19:36 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_filename_w_token_lst(t_redir ***redir, int index,
		t_token *token_root)
{
	free((*redir)[index]->filename);
	(*redir)[index]->filename = join_all_str_in_token_lst(token_root);
}

int	handle_asterisk_expansion_redir(t_redir ***redir, int index,
		t_token *token_root)
{
	t_list	*entry_lst;
	t_list	*expanded_lst;

	if (get_directory_entries(&entry_lst) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	expanded_lst = gather_matching_entries(entry_lst, token_root);
	if (ft_lstsize(expanded_lst) == 1)
	{
		free((*redir)[index]->filename);
		(*redir)[index]->filename = ft_strdup_w_check(expanded_lst->content);
	}
	else if (ft_lstsize(expanded_lst) > 1)
	{
		(free_lst(expanded_lst), free_lst(entry_lst));
		return (print_custom_err_n_return("", (*redir)[index]->filename,
			": ambiguous redirect", EXIT_FAILURE));
	}
	else
		replace_filename_w_token_lst(redir, index, token_root);
	(free_lst(expanded_lst), free_lst(entry_lst));
	return (EXIT_SUCCESS);
}

int	trim_quotes_n_expand_asterisk_redirs(t_redir ***redir, int index)
{
	t_token	*token_root;
	int		res;

	token_root = tokenize_metacharacters((*redir)[index]->filename);
	format_quotes(token_root);
	trim_quotes_for_all_tokens(token_root);
	tokenize_asterisks(&token_root);
	combine_non_asterisk_tokens(token_root);
	if (does_valid_asterisk_exist(token_root) == true)
	{
		res = handle_asterisk_expansion_redir(redir, index, token_root);
		free_tokens(token_root);
		return (res);
	}
	replace_filename_w_token_lst(redir, index, token_root);
	free_tokens(token_root);
	return (EXIT_SUCCESS);
}

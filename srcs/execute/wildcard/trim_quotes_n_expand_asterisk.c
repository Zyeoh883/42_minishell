/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes_n_expand_asterisk.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:56:33 by sting             #+#    #+#             */
/*   Updated: 2024/07/17 13:48:59 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*initialize_tokens_asterisk_expansion(char *arg)
{
	t_token	*token_root;

	token_root = tokenize_metacharacters(arg);
	format_quotes(token_root);
	trim_quotes_for_all_tokens(token_root);
	tokenize_asterisks(&token_root);
	combine_non_asterisk_tokens(token_root);
	return (token_root);
}

// loop through to find which entry matches wildcard
t_list	*gather_matching_entries(t_list *entry, t_token *token)
{
	t_list	*expanded_lst;
	t_list	*new;
	char	*dup;

	expanded_lst = NULL;
	while (entry)
	{
		if (does_entry_match_wildcard_str(entry->content, token) == true)
		{
			dup = ft_strdup(entry->content);
			if_null_perror_n_exit(dup, "ft_strdup", EXIT_FAILURE);
			new = ft_lstnew(dup);
			if_null_perror_n_exit(new, "malloc", EXIT_FAILURE);
			ft_lstadd_back(&expanded_lst, new);
		}
		entry = entry->next;
	}
	return (expanded_lst);
}

void	replace_arg_w_token_lst(char ***cmd_arg, int index, t_token *token_root)
{
	free((*cmd_arg)[index]);
	(*cmd_arg)[index] = join_all_str_in_token_lst(token_root);
}

void	replace_filename_w_token_lst(t_redir ***redir, int index,
		t_token *token_root)
{
	free((*redir)[index]->filename);
	(*redir)[index]->filename = join_all_str_in_token_lst(token_root);
}

// returns new_index after expanding wildcard
int	trim_quotes_n_expand_asterisk_args(char ***cmd_arg, int index)
{
	t_list	*entry_lst;
	t_token	*token_root;
	t_list	*expanded_lst;
	int		new_index;

	token_root = initialize_tokens_asterisk_expansion((*cmd_arg)[index]);
	new_index = index;
	if (does_valid_asterisk_exist(token_root) == true)
	{
		if (get_directory_entries(&entry_lst) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		expanded_lst = gather_matching_entries(entry_lst, token_root);
		if (ft_lstsize(expanded_lst) != 0)
		{
			replace_arg_w_expanded_lst(cmd_arg, index, expanded_lst);
			new_index = index - 1 + ft_lstsize(expanded_lst);
		}
		else
			replace_arg_w_token_lst(cmd_arg, index, token_root);
		(free_lst(expanded_lst), free_lst(entry_lst), free_tokens(token_root));
		return (new_index);
	}
	replace_arg_w_token_lst(cmd_arg, index, token_root);
	free_tokens(token_root);
	return (new_index);
}

// // ! NOT DONE
int	trim_quotes_n_expand_asterisk_redirs(t_redir ***redir, int index)
{
	t_list	*entry_lst;
	t_token	*token_root;
	t_list	*expanded_lst;

	token_root = initialize_tokens_asterisk_expansion((*redir)[index]->filename);
	if (does_valid_asterisk_exist(token_root) == true)
	{
		if (get_directory_entries(&entry_lst) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		expanded_lst = gather_matching_entries(entry_lst, token_root);
		if (ft_lstsize(expanded_lst) == 1)
		{
			free((*redir)[index]->filename);
			(*redir)[index]->filename = ft_strdup(expanded_lst->content);
			if_null_perror_n_exit((*redir)[index]->filename, "ft_strdup",
				EXIT_FAILURE);
		}
		else if (ft_lstsize(expanded_lst) > 1)
		{
			(free_lst(expanded_lst), free_lst(entry_lst),
				free_tokens(token_root));
			return (print_custom_err_n_return("", (*redir)[index]->filename,
					": ambiguous redirect", EXIT_FAILURE));
		}
		else
			replace_filename_w_token_lst(redir, index, token_root);
		(free_lst(expanded_lst), free_lst(entry_lst), free_tokens(token_root));
		return (EXIT_SUCCESS); // changed
	}
	replace_filename_w_token_lst(redir, index, token_root);
	free_tokens(token_root);
	return (EXIT_SUCCESS);
}

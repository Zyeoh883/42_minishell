/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes_n_expand_asterisk.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:56:33 by sting             #+#    #+#             */
/*   Updated: 2024/07/16 13:55:17 by sting            ###   ########.fr       */
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
			replace_arg_with_expanded_lst(cmd_arg, index, expanded_lst);
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

// t_list *lst = expanded_lst; // ! remove
// printf("====expanded_lst====\n");
// while (lst) // ! remove
// {
// 	printf("%s\n", lst->content);
// 	lst = lst->next;
// }

/*
int	trim_quotes_n_expand_asterisk_redirs(t_redir ***redir, int index)
{
	t_list	*entry_lst;
	t_list	*entry;
	t_token	*token_root;
	t_list	*expanded_lst;
	t_list	*new;
	int		new_index;

	new_index = index;
	token_root = tokenize_metacharacters((*redir)[index]->filename);
	format_quotes(token_root);
	trim_quotes_for_all_tokens(token_root);
	tokenize_asterisks(&token_root);
	if (does_valid_asterisk_exist(token_root) == true)
	{
		combine_non_asterisk_tokens(token_root);
			// ! remove
		if (get_directory_entries(&entry_lst) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		entry = entry_lst;
		expanded_lst = NULL;
		while (entry) // loop through to find which entry matches wildcard
		{
			if (does_entry_match_wildcard_str(entry->content,
					token_root) == true)
			{
				new = ft_lstnew(entry->content);
				if_null_perror_n_exit(new, "malloc", EXIT_FAILURE);
				ft_lstadd_back(&expanded_lst, new);
			}
			entry = entry->next;
		}
		if (ft_lstsize(expanded_lst) != 0)
		{
			replace_arg_with_expanded_lst(cmd_arg, index, expanded_lst);
				// ! issue
			new_index = index - 1 + ft_lstsize(expanded_lst); // added
		}
		else // added
		{
			free((*redir)[index]->filename);
			(*redir)[index]->filename = concatenate_all_str_in_token_lst(token_root);
		}
		free_list_without_freeing_content(expanded_lst); // ! not nice
		free_list(entry_lst);
		free_tokens(token_root); // added
		return (new_index); // added
	}
	free((*redir)[index]->filename);
	(*redir)[index]->filename = concatenate_all_str_in_token_lst(token_root);
	free_tokens(token_root);
	return (new_index);
}

*/
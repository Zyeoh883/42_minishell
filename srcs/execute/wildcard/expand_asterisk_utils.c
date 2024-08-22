/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_asterisk_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:56:33 by sting             #+#    #+#             */
/*   Updated: 2024/07/23 10:52:45 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	does_valid_asterisk_exist(t_token *token)
{
	while (token)
	{
		if (token->value[0] == '*' && token->type != QUOTED)
			return (true);
		token = token->next;
	}
	return (false);
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
			dup = ft_strdup_w_check(entry->content);
			new = ft_lstnew(dup);
			if_null_perror_n_exit(new, "malloc", EXIT_FAILURE);
			ft_lstadd_back(&expanded_lst, new);
		}
		entry = entry->next;
	}
	return (expanded_lst);
}

void	replace_arg_w_expanded_lst(char ***cmd_arg, int index,
		t_list *expanded_lst)
{
	char	**expanded_arr;
	int		expanded_arr_size;
	int		i;
	int		j;

	expanded_arr_size = arr_str_count(*cmd_arg) - 1 + ft_lstsize(expanded_lst);
	expanded_arr = (char **)ft_calloc(expanded_arr_size + 1, sizeof(char *));
	if_null_perror_n_exit(expanded_arr, "ft_calloc", EXIT_FAILURE);
	i = -1;
	while (++i < index)
		copy_str_to_arr(expanded_arr, i, (*cmd_arg)[i]);
	while (expanded_lst)
	{
		copy_str_to_arr(expanded_arr, i++, expanded_lst->content);
		expanded_lst = expanded_lst->next;
	}
	j = index + 1;
	while ((*cmd_arg)[j])
		copy_str_to_arr(expanded_arr, i++, (*cmd_arg)[j++]);
	free_str_arr(*cmd_arg);
	*cmd_arg = expanded_arr;
}

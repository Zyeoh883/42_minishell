/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_asterisk_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:56:33 by sting             #+#    #+#             */
/*   Updated: 2024/07/18 11:16:59 by sting            ###   ########.fr       */
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

int	rev_strncmp(const char *s1, const char *s2, size_t n)
{
	int	i;
	int	j;

	if (!n)
		return (0);
	i = ft_strlen(s1) - 1;
	j = ft_strlen(s2) - 1;
	while (i >= 0 && j >= 0 && s1[i] == s2[j] && --n > 0)
	{
		i--;
		j--;
	}
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[j]));
}

bool	does_entry_match_wildcard_str(char *entry_str, t_token *w_token)
{
	if (w_token->value[0] != '*' || w_token->type == QUOTED)
	{
		if (ft_strncmp(w_token->value, entry_str,
				ft_strlen(w_token->value)) == 0)
		{
			entry_str += ft_strlen(w_token->value);
			w_token = w_token->next;
		}
		else
			return (false);
	}
	while (w_token && w_token->next)
	{
		if (w_token->value[0] == '*' && w_token->type != QUOTED)
		{
			w_token = w_token->next;
			continue ;
		}
		// if w_token->value is string(not *) but entry_str has iterated to \0
		if (*entry_str == '\0')
			return (false);
		entry_str = ft_strnstr(entry_str, w_token->value, ft_strlen(entry_str));
		if (entry_str == NULL) // str doesn't match
			return (false);
		entry_str += ft_strlen(w_token->value);
		w_token = w_token->next;
	}
	if (w_token && (w_token->value[0] != '*' || w_token->type == QUOTED))
		if (rev_strncmp(w_token->value, entry_str,
				ft_strlen(w_token->value)) != 0)
			return (false);
	return (true);
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

// int	redir_arr_arg_count(t_redir **arr)
// {
// 	int	count;

// 	if (arr == NULL)
// 		return (0);
// 	count = 0;
// 	while (*arr != NULL)
// 	{
// 		count++;
// 		arr++;
// 	}
// 	return (count);
// }

// void	copy_str_to_redir_arr(t_redir **new_arr, int arr_index, char *str)
// {
// 	new_arr[arr_index] = (t_redir *)ft_calloc(1, sizeof(t_redir));
// 	new_arr[arr_index]->filename = ft_strdup(str);
// 	if_null_perror_n_exit(new_arr[arr_index]->filename, "ft_strdup",
		// EXIT_FAILURE);
// }

// * NEW !
// ! NOT DONE
// void	replace_redir_arg_w_expanded_lst(t_redir ***redir, int index,
// 		t_list *expanded_lst)
// {
// 	t_redir	**expanded_arr;
// 	int		expanded_arr_size;
// 	int		i;
// 	int		j;

// 	expanded_arr_size = redir_arr_arg_count(*redir) - 1
// 		+ ft_lstsize(expanded_lst);
// 	expanded_arr = (t_redir **)ft_calloc(expanded_arr_size + 1,
			// sizeof(t_redir *));
// 	if_null_perror_n_exit(expanded_arr, "ft_calloc", EXIT_FAILURE);
// 	i = -1;
// 	while (++i < index)
// 		copy_str_to_redir_arr(expanded_arr, i, (*redir)[i]->filename);
// 	while (expanded_lst)
// 	{
// 		copy_str_to_redir_arr(expanded_arr, i++, expanded_lst->content);
// 		expanded_lst = expanded_lst->next;
// 	}
// 	j = index + 1;
// 	while ((*redir)[j])
// 		copy_str_to_redir_arr(expanded_arr, i++, (*redir)[j++]->filename);
// 	free_redir_arr(*redir);
// 	*redir = expanded_arr;

// 	// print_redir_arr(*redir); // ! remove
// }

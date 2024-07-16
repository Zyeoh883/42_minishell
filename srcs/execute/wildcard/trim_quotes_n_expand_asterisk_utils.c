/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes_n_expand_asterisk_utils.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:56:33 by sting             #+#    #+#             */
/*   Updated: 2024/07/16 09:51:38 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_directory_entries(t_list **entry_lst)
{
	char			cwd[PATH_MAX];
	DIR				*dir;
	struct dirent	*entry;
	t_list			*new;
	char			*content;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (perror_and_return("getcwd", EXIT_FAILURE));
	dir = opendir(cwd);
	if (dir == NULL)
		return (perror_and_return("opendir", EXIT_FAILURE));
	*entry_lst = NULL;
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] == '.')
			continue ;
		content = ft_strdup(entry->d_name);
		if_null_perror_n_exit(content, "ft_strdup", EXIT_FAILURE);
		new = ft_lstnew(content);
		if_null_perror_n_exit(new, "malloc", EXIT_FAILURE);
		ft_lstadd_back(entry_lst, new);
	}
	if (closedir(dir) == -1)
		return (perror_and_return("closedir", EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

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

	next = cur->next; // * added
	if (cur->prev)    // if not 1st token
	{
		(cur->prev)->next = separated_lst;
		separated_lst->prev = cur->prev; // added
	}
	else
		*token_root = separated_lst;
	if (next)
		next->prev = token_last(separated_lst); // added
	token_last(separated_lst)->next = next;
	cur->next = NULL;
	free_tokens(cur);
	return (next);
}

void	tokenize_asterisks(t_token **token_root)
{
	char	*str;
	char	*start;
	t_token	*cur;
	t_token *separated_lst;
	
	cur = *token_root;
	while (cur)
	{
		if (cur->type == QUOTED)
		{
			cur = cur->next;
			continue ;
		}
		str = cur->value;
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
		cur = replace_token_with_separated_lst(token_root, cur, separated_lst);
	}
}

bool does_valid_asterisk_exist(t_token *token)
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
	int i;
	int j;

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

bool does_entry_match_wildcard_str(char *entry_str, t_token *w_token)
{
	// before everything, if 1st w_token is str,check if it matches exactly to 1st token
	if (w_token->value[0] != '*' || w_token->type == QUOTED)
	{
		if (ft_strncmp(w_token->value, entry_str, ft_strlen(w_token->value)) == 0)
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
			w_token = w_token->next; // ! added
			continue ; // skip
		}
		//if w_token->value is string(not *) but entry_str has iterated to \0
		if (*entry_str == '\0')
			return (false);
		entry_str = ft_strnstr(entry_str, w_token->value, ft_strlen(entry_str));
		if (entry_str == NULL) // str doesn't match
			return (false);	
		entry_str += ft_strlen(w_token->value);
		w_token = w_token->next;
	}
	if (w_token && (w_token->value[0] != '*' || w_token->type == QUOTED))
		if (rev_strncmp(w_token->value, entry_str, ft_strlen(w_token->value)) != 0)
			return (false);
	return (true);
}

void replace_arg_with_expanded_lst(char ***cmd_arg, int index, t_list *expanded_lst)
{
	char **expanded_arr;
	int	expanded_arr_size;
	int	i;
	int	j;
	
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

// * NEW !
// ! NOT DONE
void replace_redir_with_expanded_lst(char ***cmd_arg, int index, t_list *expanded_lst)
{
	char **expanded_arr;
	int	expanded_arr_size;
	int	i;
	int	j;
	
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

// --------------------------------

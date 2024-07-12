/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes_n_expand_asterisk.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:56:33 by sting             #+#    #+#             */
/*   Updated: 2024/07/12 16:42:49 by sting            ###   ########.fr       */
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

	t_token *separated_lst; // separate lst for expanded entries
	cur = *token_root;
	while (cur)
	{
		// if (is_str_quoted(cur->value))
		// {
		// 	cur = cur->next;
		// 	continue ;
		// }
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

// void expand_wildcard_to_all_entries()
// {

// }

int does_valid_asterisk_exist(t_token *token)
{
	while (token)
	{
		if (token->value[0] == '*' && token->type != QUOTED)
			return (true);
		token = token->next;
	}
	return (false);
}

int does_entry_match_wildcard_str(char *entry_str, t_token *w_token)
{
	// TODO: before everything, if 1st w_token is str,check if it matches exactly to 1st token
	if (w_token->value[0] != '*' || w_token->type == QUOTED)
	{
		if (ft_strncmp(w_token->value, entry_str, ft_strlen(w_token->value)) != 0)
		{
			printf("%s: "MAGENTA"check"RESET"\n", w_token->value); // ! remove
			printf(MAGENTA"entry_str: %s"RESET"\n", entry_str); // ! remove
			return (false);

		}
	}
	// entry_str += ft_strlen(w_token->value);
	// w_token = w_token->next;
	while (w_token)
	{
		if (w_token->value[0] == '*' && w_token->type != QUOTED)
		{
			w_token = w_token->next; // ! added
			continue ; // skip
		}
		// printf(GREEN"check"RESET"\n"); // ! remove
		//if w_token->value is string(not *) but entry_str has iterated to \0
		if (*entry_str == '\0')
		{
			printf("*entry_str ==/0\n");
			return (false);
		}
		entry_str = ft_strnstr(entry_str, w_token->value, ft_strlen(entry_str));
		if (entry_str == NULL) // str doesn't match
			return (false);	
		entry_str += ft_strlen(w_token->value);
		// if (at last_W_node && entry_lst havent reach \0)
		if (w_token->next == NULL && *entry_str != '\0')
		{
			printf("w_token->next == NULL && *entry_str != \'\\0\'\n");
			return (false);	
		}
		w_token = w_token->next;

	}
	return (true);
}

// int expand_asterisk(char ***cmd_arg, t_token **token, int *index)
// "logic somewhat done"
int	trim_quotes_n_expand_asterisk(char ***cmd_arg, int index)
		// "logic somewhat done"
{
	t_list *entry_lst;
	t_list *entry;
	t_token *token_root;
	t_list	*expanded_lst;
	t_list	*new;

	token_root = tokenize_metacharacters((*cmd_arg)[index]);
	format_quotes(token_root);
	trim_quotes_for_all_tokens(token_root);
	tokenize_asterisks(&token_root);
	
	// TODO: does_valid_wildcard_exist()
	if (does_valid_asterisk_exist(token_root) == true)
	{
		// printf(GREEN "----tokenize_*-----" RESET "\n"); // ! remove
		// print_tokens(token_root);                       // ! remove
		combine_non_asterisk_tokens(token_root);
		// printf(GREEN "----combine_non_*_tokens-----" RESET "\n"); // ! remove
		// print_tokens(token_root);                                 // ! remove
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

		// TODO: replace_arg_with_lst();
		t_list *lst = expanded_lst; // ! remove
		printf("====expanded_lst====\n");
		while (lst) // ! remove
		{
			printf("%s\n", lst->content);
			lst = lst->next;	
		}
		free_list_without_freeing_content(expanded_lst);
		free_list(entry_lst);

	}	
	free((*cmd_arg)[index]);
	(*cmd_arg)[index] = concatenate_all_str_in_token_lst(token_root);
	free_tokens(token_root);
	return (EXIT_SUCCESS); // TMP
}

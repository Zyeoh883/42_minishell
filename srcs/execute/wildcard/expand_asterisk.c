/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_asterisk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:56:33 by sting             #+#    #+#             */
/*   Updated: 2024/07/09 16:21:01 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_directory_entries(t_list **entry_lst)
{
	char cwd[PATH_MAX];
	DIR *dir;
	struct dirent *entry;
	t_list *new;
	char *content;

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

void	tokenize_asterisks(t_token **token_root)
{
	char *str;
	char *start;
	t_token	*new;
	t_token *token;
	t_token	*expanded_lst; // separate lst for expanded entries
	
	token = *token_root;
	while (token)
	{
		if (token->type == QUOTED)
		{
			token = token->next; 
			continue ;
		}
		str = token->value;
		expanded_lst = NULL;
		while (*str)
		{
			start = str;
			if (*str == '*')
				while (*str && *str == '*')
					str++;
			else
				while (*str && *str != '*')
					str++;
			new = str_to_token(start, str - start);
			token_add_back(&expanded_lst, new);
		}
		// replace token with expanded_lst(entries)
		if (token->prev)
			(token->prev)->next = expanded_lst;
		else 
			*token_root = expanded_lst;
		token_last(expanded_lst)->next = token->next;
		token->next = NULL;
		free_tokens(token);
		token = token_last(expanded_lst)->next;
	}
}

// void expand_wildcard_to_all_entries()
// {

// }

// int is_all_wildcard_tokens_asterisk()
// {

// }

// int does_entry_match_wildcard_str()
// {

// }

// int expand_asterisk(t_token *token, char ***cmd_arg)
// {
// 	t_list *entry_lst;
// 	int i;

// 	if (get_directory_entries(&entry_lst) == EXIT_FAILURE)
// 		return (EXIT_FAILURE);

// 	i = -1;
// 	while ((*cmd_arg)[++i])
// 	{
// 		// TODO: transfer str(s) before *
// 		if (ft_strcmp((*cmd_arg)[i], "*") == 0) // if arg -> "*"
// 		{
// 		// * store all dir entries in linked list

// 		}
// 	}

// 	free_list(entry_lst);
// 	return (EXIT_SUCCESS);
// }




// int does_entry_match_wildcard()
// {
// 	int flag;

// 	flag = YES;
// 	// TODO: before everything, if 1st token is str, check if it matches exactly to t
// 	if (token->str[0] != '*')
// 		if (ft_strncmp(w_token->str, entry_str, strlen(w_token_str)) != 0)
// 			return (NO);
// 	entry_str += strlen(w_token_str):
// 	while (w_tokens) // w_tokens == wildcard_tokens
// 	{
// 		if (token->str[0] == '*' && token->type != QUOTED)
// 			continue ; // skip
// 		if (*entry_str == '\0')
// 		//if w_token->str is string(not *) but entry_str has iterated to \0
// 			flag = NO;
// 			break ;
// 		entry_str = strnstr(entry_str, w_token->str, strlen(token->str));
// 		if (entry_str == NULL) // str doesn't match
// 			flag = NO;
// 			break;

// 		"TODO: shift ptr of entry_str by assigning to return ptr of strnstr"
// 		entry_str += ft_strlen(w_token->str);

// 		if (at last_W_node && entry_lst havent reach \0)
// 			flag = NO;
// 			break ;

// 		w_tokens = w_tokens->next;
// 	}

// 	return (flag);
// }



int expand_asterisk(char ***cmd_arg, t_token **token, int *index) // "logic somewhat done"
{
	t_list	*entry_lst;
	// t_list *entry;
	(void)cmd_arg;
	(void)index;
	
	// store dir_entries in linked list()
	if (get_directory_entries(&entry_lst) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	// TODO: 2nd round tokenizing -> separate out '*'
	// print_tokens(*token);
	printf(GREEN"----expand_*-----"RESET"\n");
	tokenize_asterisks(token);
	print_tokens(*token); // ! remove

	// TODO:
	// if (is_wildcard_tokens_all_asterisk())
	// // ^handle case where wildcard_token only has "*"
	// 	expand_wildcard_to_all_entries();
	// 	return ;

	// entry = entry_lst;
	// while (entry) // loop through to find which entry matches wildcard
	// {
	// 	if (does_entry_match_wildcard_str(entry->content, wildcard_token_lst) == true)
	// 		// lst_add_expanded() ??
	// }

	// TODO: replace all node->str in lst_expanded with wilcard str()
	free_list(entry_lst);
	return (EXIT_SUCCESS); // TMP
}

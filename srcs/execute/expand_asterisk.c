/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_asterisk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:56:33 by sting             #+#    #+#             */
/*   Updated: 2024/07/04 10:18:49 by sting            ###   ########.fr       */
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

// void expand_wildcard_to_all_entries()
// {
	
// }

// int is_all_wildcard_tokens_asterisk()
// {

// }

// int does_entry_match_wildcard_str()
// {
	
// }

// int expand_asterisk(char ***cmd_arg)
// {
// 	char cwd[PATH_MAX];
// 	struct dirent *entry;
// 	DIR *dir;
// 	t_list *entry_lst;
// 	t_list *new;
// 	char *content;
// 	int i;

// 	entry_lst = NULL;
// 	if (getcwd(cwd, sizeof(cwd)) == NULL)
// 		return (perror_and_return("getcwd", EXIT_FAILURE));
// 	dir = opendir(cwd);
// 	if (dir == NULL)
// 		return (perror_and_return("opendir", EXIT_FAILURE));
// 	// * store all dir entries in linked list
// 	while ((entry = readdir(dir)) != NULL)
// 	{
// 		if (entry->d_name[0] == '.')
// 			continue ;
// 		content = ft_strdup(entry->d_name);
// 		if_null_perror_n_exit(content, "ft_strdup", EXIT_FAILURE);
// 		new = ft_lstnew(content);
// 		if_null_perror_n_exit(new, "malloc", EXIT_FAILURE);
// 		ft_lstadd_back(&entry_lst, new);
// 	}
// 	if (closedir(dir) == -1)
// 		return (perror_and_return("closedir", EXIT_FAILURE));

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

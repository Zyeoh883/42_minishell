/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:09:17 by sting             #+#    #+#             */
/*   Updated: 2024/07/01 15:16:49 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <xmmintrin.h>

// t_list *get_directory_entries(void)
// {
// 	char cwd[PATH_MAX];
// 	struct dirent *entry;
// 	DIR *dir;
// 	t_list *entry_lst;
// 	t_list *new;

// 	if (getcwd(cwd, sizeof(cwd)) == NULL)
// 		// return (perror_and_return("getcwd", EXIT_FAILURE));
// 		return (NULL);
// 	dir = opendir(cwd);
// 	// if (dir == NULL) {
// 	// 	perror("opendir");
// 	// 	return (-1);
// 	// }

// 	// store all dir entries in linked list
// 	while ((entry = readdir(dir)) != NULL)
// 	{
// 		new = ft_lstnew(entry->d_name);
// 		if_null_perror_n_exit(new, "malloc", EXIT_FAILURE);
// 		ft_lstadd_back(&entry_lst, new);
// 	}
// 	t_list *lst = entry_lst;
// 	while (lst)
// 	{
// 		printf("entry: %s\n", lst->content);
// 		lst = lst->next;
// 	}

// 	if (closedir(dir) == -1)
// 		return (perror_and_return("closedir", EXIT_FAILURE));
// 	return (entry_lst);
// }

int	expand_asterisk(char ***cmd_arg)
{
	char cwd[PATH_MAX];
	struct dirent *entry;
	DIR *dir;
	t_list *entry_lst;
	t_list *new;

	entry_lst = NULL;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (perror_and_return("getcwd", EXIT_FAILURE));
	dir = opendir(cwd);
	if (dir == NULL)
		return (perror_and_return("opendir", EXIT_FAILURE));
	// store all dir entries in linked list
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] == '.')
			continue ;
		new = ft_lstnew(entry->d_name);
		if_null_perror_n_exit(new, "malloc", EXIT_FAILURE);
		ft_lstadd_back(&entry_lst, new);
	}
	t_list *lst = entry_lst;
	while (lst)
	{
		printf("entry: %s\n", (char *)lst->content);
		lst = lst->next;
	}
	if (closedir(dir) == -1)
		return (perror_and_return("closedir", EXIT_FAILURE));
	// 	todo: replace "*" with str(s) in linked list
	// * use -> copy_str_to_arr()

	// replace_asterisk_with_entry_lst();
	char **expanded_arr;
	int	expanded_arr_size;
	int	i;
	int	j;

	i = -1;
	while ((*cmd_arg)[++i])
	{
		// printf("outside_if\n");
		// TODO: transfer str(s) before *
		if (ft_strcmp((*cmd_arg)[i], "*") == 0) // if arg -> "*"
		{
			printf(GREEN"* detected"RESET"\n");
			// remalloc
			expanded_arr_size = arr_str_count(*cmd_arg) - 1 + ft_lstsize(entry_lst);
			expanded_arr = (char **)ft_calloc(expanded_arr_size + 1, sizeof(char *));
			if_null_perror_n_exit(expanded_arr, "ft_calloc", EXIT_FAILURE);

			j = -1;
			// transfer str(s) before *
			while (++j < i)
				copy_str_to_arr(expanded_arr, j, (*cmd_arg)[j]);
			lst = entry_lst;
			while (lst)
			{
				expanded_arr[j++] = (char *)lst->content;
				lst = lst->next;
			}
			printf("2nd arg: %s\n", expanded_arr[1]); // ! remove
			print_str_arr(expanded_arr, "expanded_arr"); // ! remove
			// TODO: transfer str(s) after *
			free(*cmd_arg);
			*cmd_arg = expanded_arr;
		}

	}

	free_lst_without_freeing_content(entry_lst);
	return (EXIT_SUCCESS);
}

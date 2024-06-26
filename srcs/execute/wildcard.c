/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:09:17 by sting             #+#    #+#             */
/*   Updated: 2024/06/26 14:43:10 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_asterisk(void)
{
	char cwd[PATH_MAX];
	struct dirent *entry;
	DIR *dir;
	int entry_count;
	t_list *entry_lst;
	t_list *new;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (print_err_and_return("getcwd", "", EXIT_FAILURE));
	dir = opendir(cwd);
	// if (dir == NULL) {
	// 	perror("opendir");
	// 	return (-1);
	// }

	// store all dir entries in linked list
	entry_count = 0;
	while ((entry = readdir(dir)) != NULL)
	{
		new = ft_lstnew(entry->d_name);
		if_null_perror_n_exit(new, "malloc", EXIT_FAILURE);
		ft_lstadd_back(&entry_lst, new);
		entry_count++;
	}
	// 	todo: replace "*" with str(s) in linked list
	t_list *lst = entry_lst;
	while (lst)
	{
		printf("entry: %s\n", lst->content);
		lst = lst->next;
	}
	
	if (closedir(dir) == -1)
		return (perror_and_return("closedir", EXIT_FAILURE));
		
	return (EXIT_SUCCESS);
}
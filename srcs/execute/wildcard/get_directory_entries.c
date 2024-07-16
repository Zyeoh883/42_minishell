/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_directory_entries.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:04:16 by sting             #+#    #+#             */
/*   Updated: 2024/07/16 10:04:27 by sting            ###   ########.fr       */
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

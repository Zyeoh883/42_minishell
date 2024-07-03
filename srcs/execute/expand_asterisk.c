/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_asterisk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:56:33 by sting             #+#    #+#             */
/*   Updated: 2024/07/03 14:24:31 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void expand_wildcard_to_all_entries()
// {
	
// }

// int is_all_wildcard_tokens_asterisk()
// {

// }

// int does_entry_match_wildcard_str()
// {
	
// }

int expand_asterisk(char ***cmd_arg)
{
	char cwd[PATH_MAX];
	DIR *dir;
	struct dirent *entry;
	t_list *entry_lst;

	entry_lst = NULL;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (perror_and_return("getcwd", EXIT_FAILURE));
	dir = opendir(cwd);
	if (dir == NULL)
		return (perror_and_return("opendir", EXIT_FAILURE));

	int	i;
	int	j;
	char *content;

	i = -1;
	while ((*cmd_arg)[++i])
	{
		// TODO: transfer str(s) before *
		if (ft_strcmp((*cmd_arg)[i], "*") == 0) // if arg -> "*"
		{
		// * store all dir entries in linked list

			free_list_without_freeing_content(entry_lst);
		}
	}
	// print_str_arr(*cmd_arg, "*cmd_arg"); // ! remove
	if (closedir(dir) == -1)
		return (perror_and_return("closedir", EXIT_FAILURE));
	return (EXIT_SUCCESS);
	
}

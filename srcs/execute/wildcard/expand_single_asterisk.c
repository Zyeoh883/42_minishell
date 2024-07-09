/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_single_asterisk.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:09:17 by sting             #+#    #+#             */
/*   Updated: 2024/07/09 15:56:22 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <xmmintrin.h>

// ! norm
int	expand_single_asterisk(char ***cmd_arg)
{
	t_list *entry_lst;
	t_list *lst;
	char **expanded_arr;
	int	expanded_arr_size;
	int	i;
	int	j;
	int asterisk_index;

	if (get_directory_entries(&entry_lst) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	i = -1;
	while ((*cmd_arg)[++i])
	{
		asterisk_index = i;
		if (ft_strcmp((*cmd_arg)[i], "*") == 0) // if arg -> "*"
		{
		// *replace_asterisk_with_entry_lst();
			// remalloc
			expanded_arr_size = arr_str_count(*cmd_arg) - 1 + ft_lstsize(entry_lst);
			expanded_arr = (char **)ft_calloc(expanded_arr_size + 1, sizeof(char *));
			if_null_perror_n_exit(expanded_arr, "ft_calloc", EXIT_FAILURE);
			// transfer str(s) before *
			j = -1;
			while (++j < i)
				copy_str_to_arr(expanded_arr, j, (*cmd_arg)[j]);
			lst = entry_lst;
			while (lst)
			{
				copy_str_to_arr(expanded_arr, j++, lst->content);
				lst = lst->next;
			}
			i++;
			while ((*cmd_arg)[i])
				copy_str_to_arr(expanded_arr, j++, (*cmd_arg)[i++]);
			i = asterisk_index + ft_lstsize(entry_lst) - 1;
			free_str_arr(*cmd_arg);
			*cmd_arg = expanded_arr;
		}
	}
	free_list(entry_lst);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:09:17 by sting             #+#    #+#             */
/*   Updated: 2024/07/08 10:14:39 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <xmmintrin.h>

int	expand_singular_asterisk(char ***cmd_arg)
{
	t_list *entry_lst;
	char **expanded_arr;
	int	expanded_arr_size;
	int	i;
	int	j;

	// print_str_arr(*cmd_arg, "cmd_arg in expand_singular_asterisk()"); // !remove
	if (get_directory_entries(&entry_lst) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	i = -1;
	while ((*cmd_arg)[++i])
	{
		// TODO: transfer str(s) before *
		if (ft_strcmp((*cmd_arg)[i], "*") == 0) // if arg -> "*"
		{
		// *replace_asterisk_with_entry_lst();
			// remalloc
			expanded_arr_size = arr_str_count(*cmd_arg) - 1 + ft_lstsize(entry_lst);
			expanded_arr = (char **)ft_calloc(expanded_arr_size + 1, sizeof(char *));
			if_null_perror_n_exit(expanded_arr, "ft_calloc", EXIT_FAILURE);
			j = -1;
			// transfer str(s) before *
			while (++j < i)
				copy_str_to_arr(expanded_arr, j, (*cmd_arg)[j]);
			t_list *lst = entry_lst;
			lst = entry_lst;
			while (lst)
			{
				copy_str_to_arr(expanded_arr, j++, lst->content);
				lst = lst->next;
			}
			i++;
			while ((*cmd_arg)[i])
				copy_str_to_arr(expanded_arr, j++, (*cmd_arg)[i++]);
			i = j - (i - 1); // i represent index one before arg that was prev after '*'
			free_str_arr(*cmd_arg);
			*cmd_arg = expanded_arr;
		}
	}
	free_list(entry_lst);
	return (EXIT_SUCCESS);

}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd_str_after_expansion.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:57:53 by sting             #+#    #+#             */
/*   Updated: 2024/06/27 14:34:34 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// - update/add additional ft_splitted strings to original char **cmd_arg
void	ft_split_cmd_arg_after_expansion(char ***cmd_arg, char *cmd_str,
		int str_index)
{
	char	**splitted;
	int		new_arr_size;
	char	**new_arr;
	int		i;
	int		j;

	(void)cmd_str;
	splitted = ft_split((*cmd_arg)[str_index], ' ');
	if_null_perror_n_exit(splitted, (*cmd_arg)[str_index], EXIT_FAILURE);
	new_arr_size = arr_str_count(*cmd_arg) - 1 + arr_str_count(splitted);
	new_arr = (char **)ft_calloc(new_arr_size + 1, sizeof(char *));
	if_null_perror_n_exit(new_arr, "ft_calloc", EXIT_FAILURE);
	i = -1;
	while (++i < str_index) // transfer str(s) until str_index
		copy_str_to_arr(new_arr, i, (*cmd_arg)[i]);
	j = -1;
	while (++j < arr_str_count(splitted)) // transfer splitted str(s)
		copy_str_to_arr(new_arr, i++, splitted[j]);
	free_str_arr(splitted);
	j = str_index + 1;
	while ((*cmd_arg)[j] != NULL) // transfer str(s) str_index + 1
		copy_str_to_arr(new_arr, i++, (*cmd_arg)[j++]);
	free_str_arr(*cmd_arg); // link new_arr to old **cmd_arg  +  FREE
	*cmd_arg = new_arr;
}

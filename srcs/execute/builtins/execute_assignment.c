/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_assignment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:49:16 by sting             #+#    #+#             */
/*   Updated: 2024/06/19 16:48:02 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_assignment(char *cmd_arg)
{
	if (ft_strchr(cmd_arg, '=') != NULL)
		if (is_var_name_valid(cmd_arg))
			return (true);
	return (false);
}

/*
 - if there is a non-assignment arg after assignement args, 
	assignment args will be trimmed off
*/
void	trim_assignments_if_cmd_present(char ***cmd_arg)
{
	int		i;
	int		new_arr_size;
	char	**new_arr;
	int j;

	i = 0;
	while ((*cmd_arg)[i] && is_assignment((*cmd_arg)[i]))
		i++;
	if (i == 0 || (*cmd_arg)[i] == NULL) // if no assignment at all || if all are assignment
		return ;
	new_arr_size = arr_str_count(*cmd_arg) - i;
	new_arr = (char **)ft_calloc(new_arr_size + 1, sizeof(char *));
	if_null_perror_n_exit(new_arr, "ft_calloc", EXIT_FAILURE);
	j = -1;
	while (++j < new_arr_size)
	{
		new_arr[j] = ft_strdup((*cmd_arg)[i++]);
		if_null_perror_n_exit(new_arr[j], "ft_strdup", EXIT_FAILURE);
	}
	free_str_arr(*cmd_arg);
	*cmd_arg = new_arr;
}

// int execute_assignment(char **cmd_arg, t_var *var_lst)
// {
// 	int	i;
// 	int	equal_index;

// 	printf(">>>>>BUILT_IN>>>>>\n");
// 	// CHECK if all assignments are valid, if 1 invalid, ALL cancelled
// 	i = -1;
// 	while (cmd_arg[++i] != NULL)
// 		if (is_var_name_valid(cmd_arg[i]) == EXIT_FAILURE)
// 			return (NOT_BUILTIN);
// 	// i = 0;
// 	return (EXIT_SUCCESS);
// }
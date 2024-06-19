/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_assignment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:49:16 by sting             #+#    #+#             */
/*   Updated: 2024/06/19 10:56:05 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int is_assignment(char **cmd_arg)
// {
	
// }

int execute_assignment(char **cmd_arg, t_var *var_lst)
{
	int	i;
	int	equal_index;

	printf(">>>>>BUILT_IN>>>>>\n");
	// CHECK if all assignments are valid, if 1 invalid, ALL cancelled
	i = -1;
	while (cmd_arg[++i] != NULL)
		if (is_var_name_valid(cmd_arg[i]) == EXIT_FAILURE)
			return (NOT_BUILTIN);
	// i = 0;
	return (EXIT_SUCCESS);
}
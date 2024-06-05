/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_assignment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:49:16 by sting             #+#    #+#             */
/*   Updated: 2024/06/05 13:10:27 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_assignment(char **cmd_arg, t_var *var_lst)
{
	int	i;
	int	equal_index;

	printf(">>>>>BUILT_IN>>>>>\n");
	i = 0;
	while (cmd_arg[++i] != NULL)
	{
		equal_index = count_chars_until_equal_sign(cmd_arg[i]);
		if (is_var_name_valid(cmd_arg[i]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		update_or_add_variable(var_lst, cmd_arg, i, equal_index);
	}
	return (EXIT_SUCCESS);
}
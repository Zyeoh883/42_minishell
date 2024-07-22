/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_assignment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:49:16 by sting             #+#    #+#             */
/*   Updated: 2024/07/22 11:03:07 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_assignment(char *cmd_arg)
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
void	remove_assignments_if_cmd_present(char ***cmd_arg)
{
	int		i;
	int		new_arr_size;
	char	**new_arr;
	int		j;

	i = 0;
	while ((*cmd_arg)[i] && is_assignment((*cmd_arg)[i]))
		i++;
	if (i == 0 || (*cmd_arg)[i] == NULL)
		return ;
	new_arr_size = arr_str_count(*cmd_arg) - i;
	new_arr = (char **)ft_calloc(new_arr_size + 1, sizeof(char *));
	if_null_perror_n_exit(new_arr, "ft_calloc", EXIT_FAILURE);
	j = -1;
	while (++j < new_arr_size)
		copy_str_to_arr(new_arr, j, (*cmd_arg)[i++]);
	free_str_arr(*cmd_arg);
	*cmd_arg = new_arr;
}

int	execute_assignment(t_simple_command *sc)
{
	int	i;

	i = -1;
	while (sc->cmd_arg[++i] != NULL)
		update_or_add_variable(sc, i,
			count_chars_until_equal_sign(sc->cmd_arg[i]), ASSIGNMENT);
	return (EXIT_SUCCESS);
}

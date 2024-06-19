/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:58:12 by sting             #+#    #+#             */
/*   Updated: 2024/06/19 10:53:59 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_or_add_variable(t_var *var_lst, char **cmd_arg, int index,
		int equal_index)
{
	char	*var_name;
	t_var	*node;

	var_name = ft_substr(cmd_arg[index], 0, equal_index);
	if_null_perror_n_exit(var_name, "ft_substr", EXIT_FAILURE);
	node = get_var_node(var_name, var_lst);
	if (node != NULL) // if variable exist
	{
		node->is_exported = true;
		if (cmd_arg[index][equal_index] == '=')
			set_var_value(var_name, &cmd_arg[index][equal_index + 1], var_lst);
	}
	else // if var don't exist
		var_lstadd_back(&var_lst, var_lstnew(cmd_arg[index], true));
	free(var_name);
}

int	execute_export(t_simple_command *sc)
{
	int		i;
	pid_t	pid;

	printf(">>>>>BUILT_IN>>>>>\n"); // ! remove
	if (sc->cmd_arg[1] == NULL)
	{
		pid = fork();
		if (pid < 0)
			perror_and_exit("fork", EXIT_FAILURE);
		else if (pid == 0)
		{
			dup2_fdin_n_fdout(sc->fd);
			exit(print_env_var(sc->var_lst, "declare -x "));
		}
		return (waitpid_n_get_exit_status(pid));
	}
	i = 0;
	while (sc->cmd_arg[++i] != NULL)
	{
		if (is_var_name_valid(sc->cmd_arg[i]) == EXIT_FAILURE)
			return (print_custom_err_n_return("export: `", sc->cmd_arg[i],
					"\': not a valid identifier", EXIT_FAILURE));
		update_or_add_variable(sc->var_lst, sc->cmd_arg, i,
			count_chars_until_equal_sign(sc->cmd_arg[i]));
	}
	return (EXIT_SUCCESS);
}

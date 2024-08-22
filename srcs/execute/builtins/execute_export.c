/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:58:12 by sting             #+#    #+#             */
/*   Updated: 2024/08/19 10:28:43 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// prints all exported vars, including those without '='
int	print_exported_var(t_var *var_lst, char *add_msg_before_var)
{
	while (var_lst != NULL)
	{
		if (var_lst->is_exported)
		{
			if (add_msg_before_var && add_msg_before_var[0] != '\0')
				ft_printf("%s", add_msg_before_var);
			ft_printf("%s\n", var_lst->str);
		}
		var_lst = var_lst->next;
	}
	return (EXIT_SUCCESS);
}

int	execute_export(t_simple_command *sc)
{
	int		i;
	pid_t	pid;

	if (sc->cmd_arg[1] == NULL)
	{
		pid = fork();
		if (pid < 0)
			perror_and_exit("fork", EXIT_FAILURE);
		else if (pid == 0)
		{
			dup2_fdin_n_fdout(sc->fd);
			exit(print_exported_var(sc->var_lst, "declare -x "));
		}
		return (waitpid_n_get_exit_status(pid));
	}
	i = 0;
	while (sc->cmd_arg[++i] != NULL)
	{
		if (is_var_name_valid(sc->cmd_arg[i]) == false)
			return (print_custom_err_n_return("export: `", sc->cmd_arg[i],
					"\': not a valid identifier", EXIT_FAILURE));
		update_or_add_variable(sc, i,
			count_chars_until_equal_sign(sc->cmd_arg[i]), EXPORT);
	}
	return (EXIT_SUCCESS);
}

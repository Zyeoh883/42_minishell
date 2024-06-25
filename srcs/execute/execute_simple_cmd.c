/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 10:15:58 by sting             #+#    #+#             */
/*   Updated: 2024/06/25 12:22:12 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_simple_cmd(t_simple_command *sc)
{
	int	ret;

	ret = EXIT_SUCCESS;
	handle_quotes_n_var_expansion(&sc->cmd_arg, sc->var_lst);
	ret = open_redir_fds(sc->redir, sc->fd, sc->var_lst);
	if (ret == EXIT_FAILURE)
		return (EXIT_FAILURE);
	// ft_printf("===Output===\n");
	if (sc->cmd_arg == NULL || *sc->cmd_arg == NULL) // no cmd at all joel was here
		return (EXIT_SUCCESS);
	remove_assignments_if_cmd_present(&sc->cmd_arg);
	ret = execute_builtins(sc);
	if (ret == NOT_BUILTIN)
		return (execute_execve(sc));	
	close_fdin_n_fdout(sc->fd);
	return (ret);
}

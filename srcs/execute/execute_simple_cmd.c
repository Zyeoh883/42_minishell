/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 10:15:58 by sting             #+#    #+#             */
/*   Updated: 2024/06/05 15:37:02 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_simple_cmd(t_simple_command *sc)
{
	int	ret_builtin;

	// print_str_arr(sc-> cmd_arg, "Before quote_handling & Expansion");
	// *print check
	handle_quotes_n_var_expansion(&sc->cmd_arg, sc->var_lst);
	// print_str_arr(sc->cmd_arg, "ft_split_after_expansion"); // *print check
	// TODO: REDIRECTION setup_redir(simple_cmd->redir);
	// if (sc->redir == NULL)
	// 	printf ("sc->redir == NULL\n");
	// if ((sc->redir)[0] == NULL)
	// 	printf ("(sc->redir)[0] == NULL\n");
	// if (((*sc->redir)->filename)[7] == '\0') 
	// 	printf("filename is null-terminated\n");
	// printf("redirr: %s\n", (*sc->redir)->filename);
	ft_printf("===Output===\n");
	if (sc->cmd_arg == NULL) // no cmd at all
		return (EXIT_SUCCESS);
	ret_builtin = execute_builtins(sc->cmd_arg, sc->var_lst);
	if (ret_builtin == NOT_BUILTIN)
		return (execute_execve(sc->cmd_arg, sc->var_lst));
	else
		return (ret_builtin);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 10:15:58 by sting             #+#    #+#             */
/*   Updated: 2024/06/06 14:11:57 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_simple_cmd(t_simple_command *sc)
{
	int	ret;

	handle_quotes_n_var_expansion(&sc->cmd_arg, sc->var_lst);
	// TODO: REDIRECTION setup_redir(simple_cmd->redir);
	// if (sc->redir == NULL)
	// 	return (printf ("sc->redir == NULL\n"));
	// if ((sc->redir)[0] == NULL)
	// 	return (printf ("(sc->redir)[0] == NULL\n"));
	// if (((*sc->redir)->filename)[7] == '\0') 
	// 	printf("filename is null-terminated\n");
	// printf("redirr: %s\n", (*sc->redir)->filename);
	ret = EXIT_SUCCESS;
	if (sc->redir && *sc->redir)
		ret = setup_redir(sc->redir);
	if (ret == EXIT_FAILURE)
		return (EXIT_FAILURE);
	
	ft_printf("===Output===\n");
	if (sc->cmd_arg == NULL) // no cmd at all
		return (EXIT_SUCCESS);
	ret = execute_builtins(sc->cmd_arg, sc->var_lst);
	if (ret == NOT_BUILTIN)
		return (execute_execve(sc->cmd_arg, sc->var_lst));
	return (ret);
}

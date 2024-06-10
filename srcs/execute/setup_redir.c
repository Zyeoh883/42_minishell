/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 10:19:56 by sting             #+#    #+#             */
/*   Updated: 2024/06/07 15:31:55by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// stores integer values of fdin & fdout in sc->fd
int	open_redir_fds(t_redir **redir, t_simple_command *sc) // ! issue -> "get_redir" name already taken 
{
	int	i;

	sc->fd[IN] = STDIN_FILENO;
	sc->fd[OUT] = STDOUT_FILENO;
	i = -1;
	if (redir == NULL)
		printf(RED"redir is NULL"RESET"\n"); // ! remove
	while (redir && redir[++i])
	{
		if ((redir[i])->type == INPUT || (redir[i])->type == HEREDOC)
			sc->fd[IN] = open((redir[i])->filename, O_RDONLY);
		else if ((redir[i])->type == OUTPUT)
			sc->fd[OUT] = open((redir[i])->filename, OUTPUT_PERMISSIONS, 0666);
		else if ((redir[i])->type == APPEND)
			sc->fd[OUT] = open((redir[i])->filename, APPEND_PERMISSIONS, 0666);
		if (sc->fd[IN] == -1 || sc->fd[OUT] == -1)
			return (perror_and_return((redir[i])->filename, EXIT_FAILURE));
	}
	return (EXIT_SUCCESS);
}

void dup2_fdin_n_fdout(int *fd)
{
	dup2(fd[IN], STDIN_FILENO);
	dup2(fd[OUT], STDOUT_FILENO);
}

void close_fdin_n_fdout(int *fd)
{
	if (fd[IN] != STDIN_FILENO)
		close(fd[IN]);
	if (fd[OUT] != STDOUT_FILENO)
		close(fd[OUT]);
}

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

// function that calls this need to check for error return val
int	expand_var_in_here_doc(char *filename, t_var *var_lst)
{
	int			fd;
	char		*content;
	struct stat	file_stat;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror_and_return(filename, EXIT_FAILURE));
	if (fstat(fd, &file_stat) == -1) 
		return (perror_and_return("fstat", EXIT_FAILURE));
	content = (char *)malloc((size_t)file_stat.st_size + 1);
	if_null_perror_n_exit(content, "malloc", EXIT_FAILURE);
	if (read(fd, content, (size_t)file_stat.st_size) == -1)
	{
		free(content);
		return (EXIT_FAILURE);
	}
	close (fd);
	content[file_stat.st_size] = '\0';
	expand_str(&content, var_lst);
	fd = open(filename, O_WRONLY | O_TRUNC);
	if (fd == -1)
		return (perror_and_return(filename, EXIT_FAILURE));
	write(fd, content, ft_strlen(content));
	close(fd);
	return (EXIT_SUCCESS);
}

// stores integer values of fdin & fdout in sc->fd
// TODO: close previously opened fd(s); currently only close last ones
int	open_redir_fds(t_redir **redir, t_simple_command *sc)
{
	int	i;

	sc->fd[IN] = STDIN_FILENO;
	sc->fd[OUT] = STDOUT_FILENO;
	i = -1;
	while (redir && redir[++i])
	{
		if ((redir[i]->type % 2 != 0) && sc->fd[IN] != STDIN_FILENO) // INPUT or HERE_DOC
			close(sc->fd[IN]);
		else if ((redir[i]->type % 2 == 0) && sc->fd[OUT] != STDOUT_FILENO) // OUTPUT or APPEND
			close(sc->fd[OUT]);
		if ((redir[i])->type == INPUT)
			sc->fd[IN] = open((redir[i])->filename, O_RDONLY);
		else if ((redir[i])->type == HEREDOC)
		{
			expand_var_in_here_doc(redir[i]->filename, sc->var_lst);
			sc->fd[IN] = open((redir[i])->filename, O_RDONLY);
		}
		else if ((redir[i])->type == OUTPUT)
			sc->fd[OUT] = open((redir[i])->filename, OUTPUT_PERMISSIONS, 0666);
		else if ((redir[i])->type == APPEND)
			sc->fd[OUT] = open((redir[i])->filename, APPEND_PERMISSIONS, 0666);
		if (sc->fd[IN] == -1 || sc->fd[OUT] == -1)
			return (perror_and_return((redir[i])->filename, EXIT_FAILURE));
	}
	return (EXIT_SUCCESS);
}

void	dup2_fdin_n_fdout(int *fd)
{
	dup2(fd[IN], STDIN_FILENO);
	dup2(fd[OUT], STDOUT_FILENO);
}

void	close_fdin_n_fdout(int *fd)
{
	if (fd[IN] != STDIN_FILENO)
		close(fd[IN]);
	if (fd[OUT] != STDOUT_FILENO)
		close(fd[OUT]);
}

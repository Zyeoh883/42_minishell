/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 10:34:27 by sting             #+#    #+#             */
/*   Updated: 2024/06/19 10:34:34 by sting            ###   ########.fr       */
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
	content = (char *)ft_calloc((size_t)file_stat.st_size + 1, sizeof(char));
	if_null_perror_n_exit(content, "ft_calloc", EXIT_FAILURE);
	if (read(fd, content, (size_t)file_stat.st_size) == -1)
	{
		free(content);
		return (perror_and_return("read", EXIT_FAILURE));
	}
	close(fd);
	expand_str(&content, var_lst);
	fd = open(filename, O_WRONLY | O_TRUNC);
	if (fd == -1)
		return (perror_and_return(filename, EXIT_FAILURE));
	write(fd, content, ft_strlen(content));
	close(fd);
	free(content);
	return (EXIT_SUCCESS);
}

void	close_previously_opened_fds(t_redir *redir, int *fd)
{
	if ((redir->type == INPUT || redir->type == HEREDOC)
		&& fd[IN] != STDIN_FILENO)
		close(fd[IN]);
	else if ((redir->type == OUTPUT || redir->type == APPEND)
		&& fd[OUT] != STDOUT_FILENO)
		close(fd[OUT]);
}

/*
	stores integer values of fdin & fdout in sc->fd
	close previously opened fd(s)
*/
int	open_redir_fds(t_redir **redir, int *fd, t_var *var_lst)
{
	int	i;

	fd[IN] = STDIN_FILENO;
	fd[OUT] = STDOUT_FILENO;
	i = -1;
	while (redir && redir[++i])
	{
		close_previously_opened_fds(redir[i], fd);
		if ((redir[i])->type == INPUT)
			fd[IN] = open((redir[i])->filename, O_RDONLY);
		else if ((redir[i])->type == HEREDOC)
		{
			if (expand_var_in_here_doc(redir[i]->filename,
					var_lst) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			fd[IN] = open((redir[i])->filename, O_RDONLY);
		}
		else if ((redir[i])->type == OUTPUT)
			fd[OUT] = open((redir[i])->filename, OUTPUT_PERMISSIONS, 0666);
		else if ((redir[i])->type == APPEND)
			fd[OUT] = open((redir[i])->filename, APPEND_PERMISSIONS, 0666);
		if (fd[IN] == -1 || fd[OUT] == -1)
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

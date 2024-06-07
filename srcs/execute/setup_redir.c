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

int	setup_redir_without_dup2(t_redir **redir)
{
	int fd_in;
	int	fd_out;
	int i;

	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	i = -1;
	while (redir && redir[++i])
	{
		if ((redir[i])->type == INPUT || (redir[i])->type == HEREDOC)
			fd_in = open((redir[i])->filename, O_RDONLY);
		else if ((redir[i])->type == OUTPUT)
			fd_out = open((redir[i])->filename, OUTPUT_PERMISSIONS, 0666);
		else if ((redir[i])->type == APPEND)
			fd_out = open((redir[i])->filename, APPEND_PERMISSIONS, 0666);
		if (fd_in == -1 || fd_out == -1)
			return (perror_and_return((redir[i])->filename, EXIT_FAILURE)); 
		if (fd_in != STDIN_FILENO)
			close(fd_in);
		if (fd_out != STDOUT_FILENO)
			close(fd_out);
	}	
	return (EXIT_SUCCESS);
}

int	*setup_redir(t_redir	**redir)
{
	int fd[2];
	int fd_in;
	int	fd_out;
	int i;

	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	i = -1;
	while (redir && redir[++i])
	{
		if ((redir[i])->type == INPUT || (redir[i])->type == HEREDOC)
			fd_in = open((redir[i])->filename, O_RDONLY);
		else if ((redir[i])->type == OUTPUT)
			fd_out = open((redir[i])->filename, OUTPUT_PERMISSIONS, 0666);
		else if ((redir[i])->type == APPEND)
			fd_out = open((redir[i])->filename, APPEND_PERMISSIONS, 0666);
		if (fd_in == -1 || fd_out == -1)
			return (perror_and_return((redir[i])->filename, EXIT_FAILURE)); 
		dup2(fd_in, STDIN_FILENO); 
		if (fd_in != STDIN_FILENO)
			close(fd_in);
		dup2(fd_out, STDOUT_FILENO);
		if (fd_out != STDOUT_FILENO)
			close(fd_out);
	}	
	return (NULL);
}


// 
/*
TODO: get_redir()

if get_redir == NULL , perror_and_return((redir[i])->filename, EXIT_FAILURE) in execute_sc()
*/
int	*get_redir(t_redir **redir)
{
	int fd_in;
	int	fd_out;
	int i;

	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	i = -1;
	while (redir && redir[++i])
	{
		if ((redir[i])->type == INPUT || (redir[i])->type == HEREDOC)
			fd_in = open((redir[i])->filename, O_RDONLY);
		else if ((redir[i])->type == OUTPUT)
			fd_out = open((redir[i])->filename, OUTPUT_PERMISSIONS, 0666);
		else if ((redir[i])->type == APPEND)
			fd_out = open((redir[i])->filename, APPEND_PERMISSIONS, 0666);
		if (fd_in == -1 || fd_out == -1)
			return (perror_and_return((redir[i])->filename, EXIT_FAILURE)); 
		if (fd_in != STDIN_FILENO)
			close(fd_in);
		if (fd_out != STDOUT_FILENO)
			close(fd_out);
	}	
	return (EXIT_SUCCESS);
}

// TODO: set_redir(t_simple_cmd *sc) -> dup2 only
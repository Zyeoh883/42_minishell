/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 10:19:56 by sting             #+#    #+#             */
/*   Updated: 2024/06/07 15:09:01 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_redir_files(t_redir	**rdr)
{
	int fd_in;
	int	fd_out;
	int i;

	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	i = -1;
	while (rdr && rdr[++i])
	{
		if ((rdr[i])->type == INPUT || (rdr[i])->type == HEREDOC)
			fd_in = open((rdr[i])->filename, O_RDONLY);
		else if ((rdr[i])->type == OUTPUT)
			fd_out = open((rdr[i])->filename, OUTPUT_PERMISSIONS, 0666);
		else if ((rdr[i])->type == APPEND)
			fd_out = open((rdr[i])->filename, APPEND_PERMISSIONS, 0666);
		if (fd_in == -1 || fd_out == -1)
			return (perror_and_return((rdr[i])->filename, EXIT_FAILURE)); 
		if (fd_in != STDIN_FILENO)
			close(fd_in);
		if (fd_out != STDOUT_FILENO)
			close(fd_out);
	}	
	return (EXIT_SUCCESS);
}

int	setup_redir(t_redir	**rdr)
{
	int fd_in;
	int	fd_out;
	int i;

	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	i = -1;
	while (rdr && rdr[++i])
	{
		if ((rdr[i])->type == INPUT || (rdr[i])->type == HEREDOC)
			fd_in = open((rdr[i])->filename, O_RDONLY);
		else if ((rdr[i])->type == OUTPUT)
			fd_out = open((rdr[i])->filename, OUTPUT_PERMISSIONS, 0666);
		else if ((rdr[i])->type == APPEND)
			fd_out = open((rdr[i])->filename, APPEND_PERMISSIONS, 0666);
		if (fd_in == -1 || fd_out == -1)
			return (perror_and_return((rdr[i])->filename, EXIT_FAILURE)); 
		dup2(fd_in, STDIN_FILENO); 
		if (fd_in != STDIN_FILENO)
			close(fd_in);
		dup2(fd_out, STDOUT_FILENO);
		if (fd_out != STDOUT_FILENO)
			close(fd_out);
	}	
	return (EXIT_SUCCESS);
}

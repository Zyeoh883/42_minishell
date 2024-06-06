/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 10:19:56 by sting             #+#    #+#             */
/*   Updated: 2024/06/06 11:21:24 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_redir(t_redir	**redir)
{
	int fd_in;
	int	fd_out;
	int count = 0; // ! remove
	
	while (*redir)
	{
		printf("count: %i\n", ++count);	// ! remove
		if (redir == NULL)
			return (printf ("redir == NULL\n"));
		if ((redir)[0] == NULL)
			return (printf ("(redir)[0] == NULL\n"));
		printf("redir: %s\n", (*redir)->filename);
		if (((*redir)->filename)[7] == '\0') // test case for "outfile"
			printf("filename is null-terminated2\n");
			
		if ((*redir)->type == INPUT)
			fd_in = open((*redir)->filename, O_RDONLY);
		else if ((*redir)->type == OUTPUT)
			fd_out = open((*redir)->filename, (O_WRONLY | O_CREAT | O_TRUNC), 0666);
		else if ((*redir)->type == HEREDOC)
			fd_in = open((*redir)->filename, O_RDONLY);
		else if ((*redir)->type == APPEND)
			fd_out = open((*redir)->filename, (O_WRONLY | O_CREAT | O_APPEND), 0666);
		// error check
		if (fd_in == -1)
			return (perror_and_return((*redir)->filename, EXIT_FAILURE)); 
			// perror("Unable to open file"); // ! not done
		else if (fd_out == -1)
			return (perror_and_return((*redir)->filename, EXIT_FAILURE)); 
			// ! ^not sure
			// perror("Unable to open file"); // ! not done
		// dup2
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
		printf(GREEN"CHECK"RESET"\n"); // ! remove
		dup2(fd_out, STDOUT_FILENO); // ! ISSUE!!!!!
		close(fd_out);
		(*redir)++;
	}	
	return (EXIT_SUCCESS);
}

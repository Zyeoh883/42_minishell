/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 10:19:56 by sting             #+#    #+#             */
/*   Updated: 2024/06/06 15:52:28 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	setup_redir(t_redir	**redir)
// {
// 	int fd_in;
// 	int	fd_out;
// 	int count = 0; // ! remove
	
// 	fd_in = STDIN_FILENO;
// 	fd_out = STDOUT_FILENO;
// 	while (*redir)
// 	{
// 		printf("count: %i\n", ++count);	// ! remove
// 		if (redir == NULL)
// 			return (printf ("redir == NULL\n"));
// 		if (*redir == NULL)
// 			return (printf ("*redir == NULL\n"));
// 		printf("redir: %s\n", (*redir)->filename); // ! ISSUE 
// 		if (((*redir)->filename)[7] == '\0') // test case for "outfile"
// 			printf("filename is null-terminated2\n");
// 		// ! ----------	
// 		if ((*redir)->type == INPUT)
// 			fd_in = open((*redir)->filename, O_RDONLY);
// 		else if ((*redir)->type == OUTPUT)
// 		{
// 			ft_printf(BLUE"OUTPUT"RESET"\n"); // ! remove 
// 			fd_out = open((*redir)->filename, (O_WRONLY | O_CREAT | O_TRUNC), 0666);
// 		}
// 		else if ((*redir)->type == HEREDOC)
// 			fd_in = open((*redir)->filename, O_RDONLY);
// 		else if ((*redir)->type == APPEND)
// 			fd_out = open((*redir)->filename, (O_WRONLY | O_CREAT | O_APPEND), 0666);
// 		// error check
// 		if (fd_in == -1)
// 			return (perror_and_return((*redir)->filename, EXIT_FAILURE)); 
// 		else if (fd_out == -1)
// 			return (perror_and_return((*redir)->filename, EXIT_FAILURE)); 
// 		// dup2
// 		if (fd_in != STDIN_FILENO)
// 		{
// 			dup2(fd_in, STDIN_FILENO); 
// 			close(fd_in);
// 		}
// 		if (fd_out != STDOUT_FILENO)
// 		{
// 			if (dup2(fd_out, STDOUT_FILENO) == -1)// ! ISSUE!!!!!
// 				return (perror_and_return("dup2", EXIT_FAILURE));
// 			printf(GREEN"CHECK"RESET"\n"); // ! remove
// 			close(fd_out);
// 		}
// 		(*redir)++;
// 	}	
// 	return (EXIT_SUCCESS);
// }

int	setup_redir(t_redir	**redir)
{
	int fd_in;
	int	fd_out;
	// int count = 0; // ! remove
	int i;

	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	i = -1;
	while (redir && redir[++i])
	{
		// printf("count: %i\n", ++count);	// ! remove
		// if (redir == NULL)
		// 	return (printf ("redir == NULL\n"));
		// if (redir[i] == NULL)
		// 	return (printf ("redir[i] == NULL\n"));
		// printf("redir: %s\n", (redir[i])->filename); // ! ISSUE 
		// if (((redir[i])->filename)[7] == '\0') // test case for "outfile"
		// 	printf("filename is null-terminated2\n");
		// // ! ----------	
		if ((redir[i])->type == INPUT)
			fd_in = open((redir[i])->filename, O_RDONLY);
		else if ((redir[i])->type == HEREDOC)
			fd_in = open((redir[i])->filename, O_RDONLY);
		else if ((redir[i])->type == OUTPUT)
			fd_out = open((redir[i])->filename, (O_WRONLY | O_CREAT | O_TRUNC), 0666);
		else if ((redir[i])->type == APPEND)
			fd_out = open((redir[i])->filename, (O_WRONLY | O_CREAT | O_APPEND), 0666);
		// error check
		if (fd_in == -1 || fd_out == -1)
			return (perror_and_return((redir[i])->filename, EXIT_FAILURE)); 
		// dup2
		dup2(fd_in, STDIN_FILENO); 
		if (fd_in != STDIN_FILENO)
			close(fd_in);
		// printf("fd_out: %d, STDOUT_FILENO: %d\n", fd_out, STDOUT_FILENO);
		// printf(CYAN"CHECK"RESET"\n"); // ! remove
		// write(fd_out, "hi", 2);
		dup2(fd_out, STDOUT_FILENO); // ! ISSUE!!!!!
		// printf(GREEN"CHECK"RESET"\n"); // ! remove
		if (fd_out != STDOUT_FILENO)
			close(fd_out);
	}	
	return (EXIT_SUCCESS);
}
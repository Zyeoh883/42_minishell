/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 10:19:56 by sting             #+#    #+#             */
/*   Updated: 2024/06/05 16:19:38 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_redir(t_redir	**redir)
{
	int fd;
	
	while (*redir)
	{
		if ((*redir)->type == INPUT)
		{
			fd = open((*redir)->filename, O_RDONLY);
			if (fd == -1)
				perror("Unable to open file"); // ! not done
			dup2()
		}
		else if ((*redir)->type == OUTPUT)
		{
			// open()
			// dup2()
		}
		else if ((*redir)->type == APPEND)
		{
			// open()
			// dup2()
		}
		else if ((*redir)->type == HEREDOC)
		{
			// open()
			// dup2()
		}
		(*redir)++;
	}

	
	return (EXIT_SUCCESS);
}

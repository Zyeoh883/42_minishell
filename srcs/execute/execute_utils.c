/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:36:48 by sting             #+#    #+#             */
/*   Updated: 2024/06/19 13:37:17 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	waitpid_n_get_exit_status(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0); // ! issue here (program hang)
	if (WIFEXITED(status))
		return (WEXITSTATUS(status)); // return exit status
	else
	{
		// TODO: Child process terminated due to a signal (handle this case)
		return (SIGNALINT);
	}
}
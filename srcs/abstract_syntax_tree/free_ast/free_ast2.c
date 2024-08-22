/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:06:45 by zyeoh             #+#    #+#             */
/*   Updated: 2024/08/22 11:07:14 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redir(t_redir **redir)
{
	int	n;

	if (!redir)
		return ;
	n = -1;
	while (redir[++n])
	{
		if (redir[n]->type == HEREDOC)
			unlink(redir[n]->filename);
		free(redir[n]->filename);
		free(redir[n]);
	}
	free(redir);
}

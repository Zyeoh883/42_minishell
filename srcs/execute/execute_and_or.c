/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_and_or.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 10:21:58 by sting             #+#    #+#             */
/*   Updated: 2024/06/20 15:26:26 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_and_or(t_and_or *and_or)
{
	int	i;
	int	j;
	int	status;

	status = execute_ast(and_or->arr_nodes[0]);
	j = -1;
	i = 1;
	while (and_or->operators[++j])
	{
		if (and_or->operators[j] == OR && status == EXIT_SUCCESS)
		{
			i++;
			continue ;
		}
		else if (and_or->operators[j] == AND && status > 0)
		{
			i++;
			continue ;
		}
		status = execute_ast(and_or->arr_nodes[i++]);
	}
	return (status);
}

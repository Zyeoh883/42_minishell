/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_and_or.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 10:21:58 by sting             #+#    #+#             */
/*   Updated: 2024/06/12 15:44:07 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * if (execute_ast() > 0) => FAIL
 * if (execute_ast() == 0) => SUCCESS
 */
// int execute_and_or(t_and_or *andor) // ! not done - LOGIC INCORRECT
// {
// 	int i;
// 	int j;

// 	i = -1;
// 	j = -1;
// 	while (andor->arr_nodes[++i] != NULL)
// 	{
// 		if (andor->operators[++j] == AND) // ! separated index for operator?
// 		{
// 			if (execute_ast(andor->arr_nodes[i]) == EXIT_SUCCESS)
// 			{
// 				continue ;
// 			}
// 			else // FAILURE
// 			{
// 				i++; // skip next node
// 			}
// 		}
// 		else if (andor->operators[i] == OR)
// 		{
// 			if (execute_ast(andor->arr_nodes[i]) == EXIT_SUCCESS)
// 			{
// 				i++;
// 			}
// 			else // FAILURE
// 			{
// 				continue ; // skip next node
// 			}
// 		}
// 	}
// }

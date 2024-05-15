/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:04:50 by sting             #+#    #+#             */
/*   Updated: 2024/05/15 10:40:14 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_env(char **my_env)
{
	if (!my_env)
		return ; // 
	int i = -1;
	while (my_env[++i] != NULL)
		printf("%s\n", my_env[i]);	
}

// ! need to return int for failure?
void execute_echo(char **cmd_arr)
{
	
}

/*
1. echo
2. cd
3. env
4. export
5. unset
6. pwd
*/
int execute_builtins(char **cmd_arr, t_var *var_lst)
{
	
}
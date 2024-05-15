/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:04:50 by sting             #+#    #+#             */
/*   Updated: 2024/05/15 13:55:29 by sting            ###   ########.fr       */
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
void execute_echo(char **cmd_arg)
{
	int i;
	int n_flag;

	n_flag = OFF;
	// TODO: check for "-n"
	if (cmd_arg[1] && ft_strlen(cmd_arg[1]) == 2 && ft_strncmp(cmd_arg[1], "-n", 2) == 0)
		n_flag = ON;
	// TODO: basic (without flag)
	i = 1;
	if (n_flag == ON)
		i = 2;
	while (cmd_arg[i] != NULL)
	{
		ft_putstr_fd(cmd_arg[i], STDOUT_FILENO);
		if (cmd_arg[i + 1] != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (n_flag == OFF)
		ft_putstr_fd("\n", STDOUT_FILENO);
}

// int ft_strcasecmp(const char *s1, const char *s2)
// {
// 	if (!s1 || !s1)
// 		return (-1);
// 	while (*s1 && *s2 && (ft_tolower(*s1) == ft_tolower(*s2)))
// 	{
// 		s1++;
// 		s2++;
// 	}
// 	return ((unsigned char)(ft_tolower(*s1)) - (unsigned char)(ft_tolower(*s2)));
// }

/*
1. echo
2. cd
3. env
4. export
5. unset
6. pwd
*/
int execute_builtins(char **cmd_arg, t_var *var_lst)
{
	(void)var_lst; // !tmp
	
	// TODO: handle mix of upper & lower case
	if (ft_strcasecmp(*cmd_arg, "echo") == 0)
		execute_echo(cmd_arg);
	else if (ft_strcasecmp(*cmd_arg, "env") == 0)
		print_env_var(var_lst);

	return (SUCCESS); // ! will built-in fail?
		
		
}
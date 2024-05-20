/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:33:19 by zyeoh             #+#    #+#             */
/*   Updated: 2024/05/20 15:39:14 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	perror_and_exit(char *str, int exit_code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	perror(str);
	exit(exit_code);
}

int	perror_and_return(char *str, int return_value)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(str);
	return (return_value);
}
// with 
int	print_err_and_return(char *str, char *perror_str, int return_value)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	perror(perror_str);
	return (return_value);
}

void if_null_perror_n_exit(void *ptr, char *str, int exit_code)
{
	if (ptr == NULL)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(str);
		exit(exit_code);
	}
}

/*
eg. print_custom_err_n_return("cd:", ": command not found", EXIT_FAILURE);
*/
int print_custom_err_n_return(char *cmd, char *cmd_arg, char *err_msg, int return_value)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(cmd_arg, STDERR_FILENO);
	ft_putendl_fd(err_msg, STDERR_FILENO);
	return (return_value);
}

void output_token_error(char *str)
{
	ft_putstr_fd("syntax error near unexpected token '", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("'", 2);
}

int arr_str_count(char **arr)
{
	int count;

	if (arr == NULL)
		return (0);
	count = 0;
	while (*arr != NULL)
	{
		count++;
		arr++;
	}
	return (count);
}

void	print_env_var(t_var *var_lst)
{
	while (var_lst != NULL)
	{
		if (var_lst->is_exported && ft_strchr(var_lst->str, '=') != NULL)
			ft_printf("%s\n", var_lst->str);
		var_lst = var_lst->next;
	}
}

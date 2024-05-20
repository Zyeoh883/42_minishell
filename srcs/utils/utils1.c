/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:33:19 by zyeoh             #+#    #+#             */
/*   Updated: 2024/05/20 13:35:06 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	perror_and_exit(char *str, int exit_code)
{
	perror(str);
	exit(exit_code);
}

int	perror_and_return(char *str, int return_value)
{
	perror(str);
	return (return_value);
}

void if_null_perror_n_exit(void *ptr, char *str, int exit_code)
{
	if (ptr == NULL)
	{
		perror(str);
		exit(exit_code);
	}
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
/*
eg. my_perror_and_return("cd:", ": command not found", EXIT_FAILURE);
*/
int my_perror_and_return(char *err_block, char *err_msg, int return_value)
{
	ft_putstr_fd(err_block, STDERR_FILENO);
	ft_putendl_fd(err_msg, STDERR_FILENO);
	return (return_value);
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

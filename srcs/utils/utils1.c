/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:33:19 by zyeoh             #+#    #+#             */
/*   Updated: 2024/05/17 15:15:46 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	perror_and_exit(char *str, int exit_code)
{
	perror(str);
	exit(exit_code);
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
eg. print_err_msg("cd:", ": command not found");
*/
void print_err_msg(char *err_block, char *msg)
{
	ft_putstr_fd(err_block, STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}

void print_str_arr(char **arr, char *title)
{
	printf("\n---%s---\n", title);
	for (int i = 0; arr[i]; i++)
		printf("%s\n", arr[i]);
	printf("-------\n");
}

void	print_var_lst(t_var *var_lst) // ! to be removed
{
	while (var_lst != NULL)
	{
		ft_printf("%s\n", var_lst->str);
		var_lst = var_lst->next;
	}
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

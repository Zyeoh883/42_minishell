/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:33:19 by zyeoh             #+#    #+#             */
/*   Updated: 2024/06/03 17:36:36 by zyeoh            ###   ########.fr       */
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

// example output> minishell: cd: /invalid_path: "perror message"
int	print_err_and_return(char *str, char *perror_str, int return_value)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	perror(perror_str);
	return (return_value);
}

/*
eg. print_custom_err_n_return("cd:", ": command not found", EXIT_FAILURE);
*/
int	print_custom_err_n_return(char *cmd, char *cmd_arg, char *err_msg,
		int return_value)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(cmd_arg, STDERR_FILENO);
	ft_putendl_fd(err_msg, STDERR_FILENO);
	return (return_value);
}

void	if_null_perror_n_exit(void *ptr, char *str, int exit_code)
{
	if (ptr == NULL)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(str);
		exit(exit_code);
	}
}

void	output_token_error(char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("'", 2);
}

void	output_eof_error(char quote)
{
	if (ft_strchr("\"\'", quote))
	{
		ft_putstr_fd("minishell: unexpected EOF while looking for matching `", 2);
		ft_putchar_fd(quote, 2);
		ft_putendl_fd("'", 2);
	}
	ft_putendl_fd("minishell: syntax error: unexpected end of file", 2);
}

int	is_metacharacter(char c)
{
	if (ft_strchr(METACHARACTERS, c))
		return (1);
	return (0);
}

int	is_operand(char c)
{
	if (ft_strchr(OPERAND, c))
		return (1);
	return (0);
}

int	is_banned_char(char c)
{
	if (ft_strchr(BANNED_CHARACTERS, c))
		return (1);
	return (0);
}

long	ft_atol(const char *str)
{
	long	result;
	int		sign;

	while ((9 <= *str && *str <= 13) || *str == ' ')
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	result = 0;
	while ('0' <= *str && *str <= '9')
	{
		result *= 10;
		result += *str - '0';
		str++;
	}
	return (result * sign);
}

int	arr_str_count(char **arr)
{
	int	count;

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

int	print_env_var(t_var *var_lst, char *add_msg_before_var)
{
	while (var_lst != NULL)
	{
		if (var_lst->is_exported && ft_strchr(var_lst->str, '=') != NULL)
		{
			if (add_msg_before_var && add_msg_before_var[0] != '\0')
				ft_printf("%s", add_msg_before_var);
			ft_printf("%s\n", var_lst->str);
		}
		var_lst = var_lst->next;
	}
	return (EXIT_SUCCESS);
}

// void print_str_arr(char **arr, char *title)
// {
// 	printf("\n---%s---\n", title);
// 	for (int i = 0; arr[i]; i++)
// 		printf("%s\n", arr[i]);
// 	printf("-------\n");
// }

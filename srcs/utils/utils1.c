/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:33:19 by zyeoh             #+#    #+#             */
/*   Updated: 2024/07/18 15:26:13 by sting            ###   ########.fr       */
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
		ft_putstr_fd("minishell: unexpected EOF while looking for matching `",
			STDERR_FILENO);
		ft_putchar_fd(quote, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
	}
	ft_putendl_fd("minishell: syntax error: unexpected end of file", STDERR_FILENO);
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

void	copy_str_to_arr(char **new_arr, int arr_index, char *str)
{
	new_arr[arr_index] = ft_strdup(str);
	if_null_perror_n_exit(new_arr[arr_index], "ft_strdup", EXIT_FAILURE);
}

int	count_words(char const *str)
{
	int	count;
	int	flag;

	count = 0;
	flag = 1;
	while (*str)
	{
		if (*str != ' ' && flag == 1)
		{
			count++;
			flag = 0;
		}
		if (*str == ' ')
			flag = 1;
		str++;
	}
	return (count);
}

char	*ft_strdup_w_check(char *str)
{
	char *dup;

	dup = ft_strdup(str);
	if_null_perror_n_exit(dup, "ft_strdup", EXIT_FAILURE);
	return (dup);
}

int	rev_strncmp(const char *s1, const char *s2, size_t n)
{
	int	i;
	int	j;

	if (!n)
		return (0);
	if (!*s1)
		i = 0;
	else
		i = ft_strlen(s1) - 1;
	if (!*s2)
		j = 0;
	else
		j = ft_strlen(s2) - 1;
	while (i >= 0 && j >= 0 && s1[i] == s2[j] && --n > 0)
	{
		i--;
		j--;
	}
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[j]));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:33:19 by zyeoh             #+#    #+#             */
/*   Updated: 2024/05/24 19:05:38 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	perror_and_exit(char *str, int exit_code)
{
	perror(str);
	reset_terminal();
	exit(exit_code);
}

int	perror_and_return(char *str, int return_value)
{
	perror(str);
	return (return_value);
}

void	free_split(char **split)
{
	char	**head;

	if (!split)
		return ;
	head = split;
	while (*head != NULL)
	{
		free(*head);
		head++;
	}
	free(split);
}

int	is_metacharacter(char c)
{
	char	*metacharacters;

	metacharacters = METACHARACTERS;
	while (*metacharacters)
	{
		if (c == *metacharacters)
			return (1);
		metacharacters++;
	}
	return (0);
}

int	is_operand(char c)
{
	char	*operand;

	operand = OPERAND;
	while (*operand)
	{
		if (c == *operand)
			return (1);
		operand++;
	}
	return (0);
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

// samuel utils below

void if_null_perror_n_exit(void *ptr, char *str, int exit_code)
{
	if (ptr == NULL)
	{
		perror(str);
		exit(exit_code);
	}
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

void print_str_arr(char **arr, char *title)
{
	printf("\n---%s---\n", title);
	for (int i = 0; arr[i]; i++)
		printf("%s\n", arr[i]);
	printf("-------\n");
}

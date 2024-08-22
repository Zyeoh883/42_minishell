/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:47:01 by zyeoh             #+#    #+#             */
/*   Updated: 2024/08/22 10:47:12 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	*dup;

	dup = ft_strdup(str);
	if_null_perror_n_exit(dup, "ft_strdup", EXIT_FAILURE);
	return (dup);
}

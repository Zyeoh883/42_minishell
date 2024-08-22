/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:33:19 by zyeoh             #+#    #+#             */
/*   Updated: 2024/08/22 10:48:33 by zyeoh            ###   ########.fr       */
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

void	if_null_perror_n_exit(void *ptr, char *str, int exit_code)
{
	if (ptr == NULL)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(str);
		exit(exit_code);
	}
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

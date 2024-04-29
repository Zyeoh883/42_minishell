/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:33:19 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/29 17:11:50 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	perror_and_exit(char *str, int exit_code)
{
	perror(str);
	exit(exit_code);
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

void output_token_error(char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("'", 2);
}

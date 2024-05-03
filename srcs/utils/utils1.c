/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:33:19 by zyeoh             #+#    #+#             */
/*   Updated: 2024/05/03 09:24:34 by sting            ###   ########.fr       */
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


void output_token_error(char *str)
{
	ft_putstr_fd("syntax error near unexpected token '", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("'", 2);
}
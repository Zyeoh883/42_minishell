/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:46:15 by zyeoh             #+#    #+#             */
/*   Updated: 2024/08/22 10:46:35 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	ft_putendl_fd("minishell: syntax error: unexpected end of file",
		STDERR_FILENO);
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

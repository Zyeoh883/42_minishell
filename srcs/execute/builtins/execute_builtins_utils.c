/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:07:33 by sting             #+#    #+#             */
/*   Updated: 2024/06/05 13:08:27 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_chars_until_equal_sign(char *str)
{
	int	count;

	count = 0;
	while (str[count] && str[count] != '=')
		count++;
	return (count);
}

int	is_var_name_valid(char *var_name)
{
	int		j;

	if (!(ft_isalpha(var_name[0]) || var_name[0] == '_'))
		return (EXIT_FAILURE);
	j = 0;
	while (var_name[j] && var_name[j] != '=')
	{
		if (!(ft_isalnum(var_name[j]) || var_name[j] == '_'))
			return (EXIT_FAILURE);
		j++;
	}
	return (EXIT_SUCCESS);
}

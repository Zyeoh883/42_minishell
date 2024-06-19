/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:07:33 by sting             #+#    #+#             */
/*   Updated: 2024/06/19 14:23:14 by sting            ###   ########.fr       */
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

// iterates through str till '=' is reached
int	is_var_name_valid(char *var_name)
{
	int		j;

	if (!(ft_isalpha(var_name[0]) || var_name[0] == '_'))
		return (false);
	j = 0;
	while (var_name[j] && var_name[j] != '=')
	{
		if (!(ft_isalnum(var_name[j]) || var_name[j] == '_'))
			return (false);
		j++;
	}
	return (true);
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

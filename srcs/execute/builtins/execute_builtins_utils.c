/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:07:33 by sting             #+#    #+#             */
/*   Updated: 2024/06/04 14:17:52 by sting            ###   ########.fr       */
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

int	is_var_name_valid(char *var_name, t_builtin_type type)
{
	int		j;
	char	*printed_str;

	if (type == EXPORT)
		printed_str = "export: `";
	else if (type == UNSET)
		printed_str = "unset: `";
	j = -1;
	if (!ft_isalpha(var_name[0]) && var_name[0] != '_')
		return (print_custom_err_n_return(printed_str, var_name,
				"\': not a valid identifier", EXIT_FAILURE));
	while (var_name[++j] && var_name[++j] != '=')
		if (!(ft_isalnum(var_name[j]) || var_name[j] == '_'))
			return (print_custom_err_n_return(printed_str, var_name,
					"\': not a valid identifier", EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

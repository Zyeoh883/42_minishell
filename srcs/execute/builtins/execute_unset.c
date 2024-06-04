/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:59:30 by sting             #+#    #+#             */
/*   Updated: 2024/06/04 15:04:57 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
TODO: set the prev->next to point to curr->next
	store prev;
*/
void	delete_var_from_var_lst(char *var_name, t_var **var_lst)
{
	int		name_len;
	t_var	*prev;
	t_var	*next;
	t_var	*var;

	var = *var_lst;
	prev = NULL;
	while (var != NULL)
	{
		next = var->next;
		name_len = count_chars_until_equal_sign(var->str);
		if ((ft_strncmp(var->str, var_name, name_len) == 0)
			&& (ft_strncmp(var->str, var_name, ft_strlen(var_name)) == 0))
		{
			if (prev == NULL) // if 1st node
				*var_lst = var->next;
			else
				prev->next = var->next;
			free(var->str);
			free(var);
		}
		else
			prev = var;
		var = next;
	}
}

/*
features:
	- can have unlimited arg
*/
int	execute_unset(char **cmd_arg, t_var *var)
{
	int	i;

	ft_printf(">>>>>BUILT_IN>>>>>\n");
	i = 0;
	while (cmd_arg[++i])
	{
		if (is_var_name_valid(cmd_arg[i], UNSET) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		delete_var_from_var_lst(cmd_arg[i], &var);
	}
	return (EXIT_SUCCESS);
}

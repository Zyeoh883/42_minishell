/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:59:30 by sting             #+#    #+#             */
/*   Updated: 2024/07/22 11:05:37 by sting            ###   ########.fr       */
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
			if (prev == NULL)
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
int	execute_unset(t_simple_command *sc)
{
	int	i;

	i = 0;
	while (sc->cmd_arg[++i])
	{
		if (is_var_name_valid(sc->cmd_arg[i]) == false)
			return (print_custom_err_n_return("unset: `", sc->cmd_arg[i],
					"\': not a valid identifier", EXIT_FAILURE));
		delete_var_from_var_lst(sc->cmd_arg[i], &sc->var_lst);
	}
	return (EXIT_SUCCESS);
}

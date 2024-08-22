/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:07:33 by sting             #+#    #+#             */
/*   Updated: 2024/07/22 11:05:08 by sting            ###   ########.fr       */
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
bool	is_var_name_valid(char *var_name)
{
	int	j;

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

/*
code logic:

if (var exist)
	____;
else if (var_don't exist)
	____:
*/
void	update_or_add_variable(t_simple_command *sc, int index, int equal_index,
		t_builtin_type type)
{
	char	*var_name;
	t_var	*node;

	var_name = ft_substr(sc->cmd_arg[index], 0, equal_index);
	if_null_perror_n_exit(var_name, "ft_substr", EXIT_FAILURE);
	node = get_var_node(var_name, sc->var_lst);
	if (node != NULL)
	{
		if (type == EXPORT)
			node->is_exported = true;
		if (sc->cmd_arg[index][equal_index] == '=')
			set_var_value(var_name, &sc->cmd_arg[index][equal_index + 1],
				sc->var_lst);
	}
	else
	{
		if (type == EXPORT)
			var_lstadd_back(&sc->var_lst, var_lstnew(sc->cmd_arg[index], true));
		if (type == ASSIGNMENT)
			var_lstadd_back(&sc->var_lst, var_lstnew(sc->cmd_arg[index],
					false));
	}
	free(var_name);
}

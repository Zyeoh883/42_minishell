/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:04:46 by sting             #+#    #+#             */
/*   Updated: 2024/05/10 15:14:39 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*var_lstlast(t_var *lst) // tested
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_var	*var_lstnew(char *str)
{
	t_var	*new_node;

	new_node = (t_var *)ft_calloc(1, sizeof(t_var));
	if_null_perror_n_exit(new_node, "ft_calloc", EXIT_FAILURE);
	new_node->str = ft_strdup(str);
	if_null_perror_n_exit(new_node->str, "ft_strdup", EXIT_FAILURE);
	new_node->next = NULL;
	new_node->is_exported = NO;
	new_node->exit_status = 0;
	return (new_node);
}

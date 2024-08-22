/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_lst_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:04:46 by sting             #+#    #+#             */
/*   Updated: 2024/07/22 10:47:32 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*var_lstlast(t_var *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_var	*var_lstnew(char *str, int is_exported)
{
	t_var	*new_node;

	new_node = (t_var *)ft_calloc(1, sizeof(t_var));
	if_null_perror_n_exit(new_node, "ft_calloc", EXIT_FAILURE);
	new_node->str = ft_strdup(str);
	if_null_perror_n_exit(new_node->str, "ft_strdup", EXIT_FAILURE);
	new_node->next = NULL;
	new_node->is_exported = is_exported;
	return (new_node);
}

void	var_lstadd_front(t_var **lst, t_var *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

void	var_lstadd_back(t_var **lst, t_var *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
	{
		var_lstlast(*lst)->next = new;
		return ;
	}
	(*lst) = new;
}

void	free_var_lst(t_var *list)
{
	t_var	*next;

	while (list != NULL)
	{
		next = list->next;
		free(list->str);
		free(list);
		list = next;
	}
}

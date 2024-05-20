/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 09:57:53 by sting             #+#    #+#             */
/*   Updated: 2024/05/20 13:46:10 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*convert_env_to_linked_list(char **env)
{
	int		i;
	t_var	*head;
	t_var	*tail;
	t_var	*new_node;

	i = -1;
	head = NULL;
	while (env[++i] != NULL)
	{
		new_node = var_lstnew(env[i], true);
		if (head == NULL)
		{
			head = new_node;
			tail = new_node;
		}
		else
		{
			tail->next = new_node;
			tail = new_node;
		}
	}
	var_lstadd_front(&head, var_lstnew("?=0", false));
	return (head);
}

/*
* TAKE NOTE
	- strings stored in returned array share the same memory as strings stored in env_lst
*/
char	**convert_var_lst_to_array(t_var *var_list)
{
	int		count;
	int		i;
	char	**var_arr;
	t_var	*current;

	count = 0;
	current = var_list;
	while (current != NULL) // ft_lstsize
	{
		count++;
		current = current->next;
	}
	var_arr = (char **)ft_calloc((count + 1), sizeof(char *));
	if_null_perror_n_exit(var_arr, "ft_calloc", EXIT_FAILURE);
	// Copy each environment variable string into the array
	current = var_list;
	i = 0;
	while (current != NULL)
	{
		var_arr[i] = current->str;
		current = current->next;
		i++;
	}
	return (var_arr);
}

char	*get_var_value(const char *name, t_var *var)
{
	char	*equal_sign;

	if (var == NULL)
		return (NULL);
	while (var != NULL)
	{
		equal_sign = ft_strchr(var->str, '=');
		if (equal_sign != NULL)
			if ((ft_strncmp(var->str, name, equal_sign - var->str) == 0)
				&& (ft_strncmp(var->str, name, ft_strlen(name)) == 0))
				return (equal_sign + 1);
		var = var->next;
	}
	return (NULL); // Environment variable not found
}

void set_var_value(char *var_name, char *new_content, t_var *var)
{
	char *equal_sign;
	char *updated;

	while (var != NULL)
	{
		equal_sign = ft_strchr(var->str, '=');
		if (equal_sign != NULL)
			if ((ft_strncmp(var->str, var_name, equal_sign - var->str) == 0)
				&& (ft_strncmp(var->str, var_name, ft_strlen(var_name)) == 0))
			{
				updated = (char *)malloc(ft_strlen(var_name) + 1 + ft_strlen(new_content) + 1);
				ft_strlcpy(updated, var->str, (equal_sign - var->str + 1 + 1)); // + 1 for
				ft_strlcpy(&updated[ft_strlen(var_name) + 1], new_content, ft_strlen(new_content) + 1);
				free(var->str);
				var->str = updated;
				// printf("updated: %s\n", var->str);
				// if (ft_strncmp("?", var_name, 1) == 0)
				// 	free(new_content);
				return ;
			}
		var = var->next;
	}
}

t_var	*get_var_node(const char *name, t_var *var)
{
	char	*equal_sign;

	if (var == NULL)
		return (NULL);
	while (var != NULL)
	{
		equal_sign = ft_strchr(var->str, '=');
		if (equal_sign != NULL)
			if ((ft_strncmp(var->str, name, equal_sign - var->str) == 0)
				&& (ft_strncmp(var->str, name, ft_strlen(name)) == 0))
				return (var);
		var = var->next;
	}
	return (NULL); // Environment variable not found
}

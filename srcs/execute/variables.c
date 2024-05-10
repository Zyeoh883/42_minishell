/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 09:57:53 by sting             #+#    #+#             */
/*   Updated: 2024/05/10 16:21:01 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_var	*convert_env_to_linked_list(char **env)
// {
// 	int		i;
// 	t_var	*head;
// 	t_var	*tail;
// 	t_var	*new_node;

// 	i = -1;
// 	// head = NULL;
// 	// initialise first var as "?=0"
// 	head = var_lstnew("?=0");
// 	while (env[++i] != NULL)
// 	{
// 		new_node = var_lstnew(env[i]);
// 		new_node->is_exported = 1;
// 		if (head == NULL)
// 		{
// 			head = new_node;
// 			tail = new_node;
// 		}
// 		else
// 		{
// 			tail->next = new_node;
// 			tail = new_node;
// 		}
// 	}
// 	return (head);
// }

t_var	*convert_env_to_linked_list(char **env)
{
	int		i;
	t_var	*head;
	t_var	*tail;
	t_var	*new_node;

	i = -1;
	// head = NULL;
	// initialise first var as "?=0"
	head = var_lstnew("?=hello");
	tail = head;
	while (env[++i] != NULL)
	{
		new_node = var_lstnew(env[i]);
		new_node->is_exported = 1;
		tail->next = new_node;
		tail = new_node;
	}
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
	char	**my_env;
	t_var	*current;

	count = 0;
	current = var_list;
	while (current != NULL) // ft_lstsize
	{
		// if (current->is_exported) //!
			count++;
		current = current->next;
	}
	my_env = (char **)ft_calloc((count + 1), sizeof(char *));
	if_null_perror_n_exit(my_env, "ft_calloc", EXIT_FAILURE);
	// Copy each environment variable string into the array
	current = var_list;
	i = 0;
	while (current != NULL)
	{
		// if (current->is_exported) //!
			my_env[i] = current->str;
		current = current->next;
		i++;
	}
	return (my_env);
}

// char *my_getvar(const char *name, char **my_env)
// {
// 	char *equal_sign;

// 	if (my_env == NULL)
// 		return (NULL);
// 	while (*my_env != NULL)
// 	{
//         // Find the position of '=' in the current environment variable
//         equal_sign = ft_strchr(*my_env, '=');
//         if (equal_sign != NULL)
//            
	// Compare the name of the environment variable with the given name
//             // if (ft_strncmp(*my_env, name, equal_sign - *my_env) == 0) {
//             if ((ft_strncmp(*my_env, name, equal_sign - *my_env) == 0)
	// && (ft_strncmp(*my_env, name, ft_strlen(name)) == 0))
//                 return (equal_sign + 1);
	// Return a pointer to the value part of the environment variable
//         my_env++;
//     }
//     return (NULL); // Environment variable not found
// }

char	*my_getvar(const char *name, t_var *var)
{
	char	*equal_sign;
	// char *exit_status;

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

void	print_env_var(t_var *env_list)
{
	while (env_list != NULL)
	{
		if (env_list->is_exported)
			ft_printf("%s\n", env_list->str);
		env_list = env_list->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 09:57:53 by sting             #+#    #+#             */
/*   Updated: 2024/05/10 15:03:09 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_var	*var_lstlast(t_var *lst) // tested
// {
// 	if (!lst)
// 		return (NULL);
// 	while (lst->next)
// 		lst = lst->next;
// 	return (lst);
// }

// t_var	*var_lstnew(char *str)
// {
// 	t_var	*new_node;

// 	new_node = (t_var *)ft_calloc(1, sizeof(t_var));
// 	if_null_perror_n_exit(new_node, "ft_calloc", EXIT_FAILURE);
// 	new_node->str = ft_strdup(str);
// 	if_null_perror_n_exit(new_node->str, "ft_strdup", EXIT_FAILURE);
// 	new_node->next = NULL;
// 	return (new_node);
// }

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
		new_node = var_lstnew(env[i]);
		new_node->is_exported = 1;
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
	return (head);
}
/*
* TAKE NOTE
	- strings stored in returned array share the same memory as strings stored in env_lst
*/
char	**convert_var_lst_to_array(t_var *env_list)
{
	int		count;
	int		i;
	char	**my_env;
	t_var	*current;

	count = 0;
	current = env_list;
	while (current != NULL) // ft_lstsize
	{
		count++;
		current = current->next;
	}
	my_env = (char **)ft_calloc((count + 1), sizeof(char *));
	if_null_perror_n_exit(my_env, "ft_calloc", EXIT_FAILURE);
	// Copy each environment variable string into the array
	current = env_list;
	i = 0;
	while (current != NULL)
	{
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
	char *exit_status;

	if (var == NULL)
		return (NULL);
	// TODO: edge case for $?
	if (ft_strncmp(name, "?", ft_strlen(name)) == 0) // if $?
	{
		exit_status = ft_itoa(var->exit_status); 		
		if_null_perror_n_exit(exit_status, "ft_itoa", EXIT_FAILURE);
		return (exit_status);
	}
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
			ft_printf("%s", env_list->str);
		env_list = env_list->next;
	}
}

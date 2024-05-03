/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 09:57:53 by sting             #+#    #+#             */
/*   Updated: 2024/05/03 10:19:48 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_var	*env_lstlast(t_env_var *lst) // tested
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

// void env_lstadd_back(t_env_var **env_list, t_env_var *new_node)
// {
// 	if (!env_list || !new_node)
// 		return ;
// 	if (*env_list)
// 	{
// 		env_lstlast(*env_list)->next = new_node;
// 		return ;
// 	}
// 	(*env_list) = new_node;
// }

t_env_var	*env_lstnew(char *str)
{
	t_env_var	*new_node;

	new_node = (t_env_var *)malloc(sizeof(t_env_var));
	if (new_node == NULL)
		perror_and_exit("malloc", EXIT_FAILURE);
	new_node->str = ft_strdup(str);
	if (new_node->str == NULL)
		perror_and_exit("strdup", EXIT_FAILURE);
	new_node->next = NULL;
	return (new_node);
}

t_env_var	*convert_env_to_linked_list(char **env)
{
	int			i;
	t_env_var	*head;
	t_env_var	*tail;
	t_env_var	*new_node;

	i = -1;
	while (env[++i] != NULL)
	{
		new_node = env_lstnew(env[i]);
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
char	**convert_env_lst_to_array(t_env_var *env_list)
{
    // Count the number of nodes in the linked list
    int count;
	int i;
	char **my_env;
    t_env_var *current;
	
	count = 0;
	current = env_list;
    while (current != NULL) // ft_lstsize
	{
        count++;
        current = current->next;
    }
    // Allocate memory for the char ** array
    my_env = (char **)malloc((count + 1) * sizeof(char *));
    if (my_env == NULL)
		perror_and_exit("malloc", EXIT_FAILURE);
    // Copy each environment variable string into the array
    current = env_list;
    i = 0;
    while (current != NULL) 
	{
        my_env[i] = current->str;
        current = current->next;
        i++;
    }
    // Set the last element of the array to NULL to indicate the end
    my_env[count] = NULL;
    return (my_env);
}

char *my_getenv(const char *name, char **my_env) 
{
	char *equal_sign;

	if (my_env == NULL)
		return (NULL);
	while (*my_env != NULL) 
	{
        // Find the position of '=' in the current environment variable
        equal_sign = ft_strchr(*my_env, '=');
        if (equal_sign != NULL) {
            // Compare the name of the environment variable with the given name
            // if (ft_strncmp(*my_env, name, equal_sign - *my_env) == 0) {
            if ((ft_strncmp(*my_env, name, equal_sign - *my_env) == 0) && (ft_strncmp(*my_env, name, ft_strlen(name)) == 0)) {

                // Return a pointer to the value part of the environment variable
                return (equal_sign + 1);
            }
        }
        my_env++;
    }
    // Environment variable not found
    return (NULL);
}

// void print_env_var(t_env_var *env_list) {
//     t_env_var *current = env_list;

//     while (current != NULL) {
//         // Print the environment variable string
//         printf("%s", current->str);

//         // Print the is_exported value
//         printf(" (is_exported: %d)\n", current->is_exported);

//         // Move to the next node
//         current = current->next;
//     }
// }
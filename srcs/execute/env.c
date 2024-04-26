/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 09:57:53 by sting             #+#    #+#             */
/*   Updated: 2024/04/26 10:38:03 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_var	*custom_ft_lstnew(char *str)
{
	t_env_var	*new_node;

	new_node = (t_env_var *)malloc(sizeof(t_env_var));
	if (new_node == NULL)
		perror_and_exit("malloc", EXIT_FAILURE);
	new_node->str = ft_strdup(str);
	if (new_node->str == NULL)
		perror_and_exit("strdup", EXIT_FAILURE);
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
		new_node = custom_ft_lstnew(env[i]);
		new_node->next = NULL;
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
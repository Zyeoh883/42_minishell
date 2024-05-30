/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:46:03 by sting             #+#    #+#             */
/*   Updated: 2024/05/30 12:11:22 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void set_exit_status(int exit_code, t_var *var_lst)
{
	char *str;
	char *updated;
	t_var *exit_status;

	print_var_lst(var_lst);
	// if (var_lst == NULL)
		// printf("var_lst is NULL in set_exit_status\n"); // ! ISSUE: var_lst is not assign in t_NODE
	exit_status = get_var_node("?", var_lst);
	if (exit_status == NULL)
	{
		// ft_putstr_fd("Exit status node can't be found in var_lst\n", STDERR_FILENO);
		return ;
	}
	str = ft_itoa(exit_code);
	if_null_perror_n_exit(str, "ft_itoa", EXIT_FAILURE);
	updated = (char *)malloc(1 + 1 + ft_strlen(str) + 1);
	ft_strlcpy(updated, "?=", (2 + 1)); // + 1 for
	ft_strlcpy(&updated[2], str, ft_strlen(str) + 1);
	free(str);
	free(exit_status->str);
	exit_status->str = updated;
}

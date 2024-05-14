/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:46:03 by sting             #+#    #+#             */
/*   Updated: 2024/05/14 10:43:30 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void set_exit_status(int exit_code, t_var *var_lst)
// {
// 	char *str;

// 	str = ft_itoa(exit_code);
// 	if_null_perror_n_exit(str, "ft_itoa", EXIT_FAILURE);
// 	set_var("?", str, var_lst);
// }

// VER 2
void set_exit_status(int exit_code, t_var *var_lst)
{
	char *str;
	char *updated;

	str = ft_itoa(exit_code);
	if_null_perror_n_exit(str, "ft_itoa", EXIT_FAILURE);
	updated = (char *)malloc(1 + 1 + ft_strlen(str) + 1);
	ft_strlcpy(updated, "?=", (2 + 1)); // + 1 for
	ft_strlcpy(&updated[2], str, ft_strlen(str) + 1);
	// printf("str: %p\n", str);
	free(str);
	// printf("str: %p\n", str);
	free(var_lst->str);
	// printf("var->str: %p\n", var_lst->str);
	var_lst->str = updated;
}

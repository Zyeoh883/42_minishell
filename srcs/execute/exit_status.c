/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:46:03 by sting             #+#    #+#             */
/*   Updated: 2024/06/04 09:21:07 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_exit_status(int exit_code, t_var *var_lst)
{
	char	*str;
	char	*updated;
	t_var	*exit_status;

	exit_status = get_var_node("?", var_lst);
	str = ft_itoa(exit_code);
	if_null_perror_n_exit(str, "ft_itoa", EXIT_FAILURE);
	updated = (char *)malloc(1 + 1 + ft_strlen(str) + 1);
	ft_strlcpy(updated, "?=", (2 + 1));
	ft_strlcpy(&updated[2], str, ft_strlen(str) + 1);
	free(str);
	free(exit_status->str);
	exit_status->str = updated;
}

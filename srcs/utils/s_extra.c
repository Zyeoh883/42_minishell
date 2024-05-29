/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:02:06 by sting             #+#    #+#             */
/*   Updated: 2024/05/17 16:03:22 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	print_var_lst(t_var *var_lst)
{
	while (var_lst != NULL)
	{
		ft_printf("%s\n", var_lst->str);
		var_lst = var_lst->next;
	}
}

void print_str_arr(char **arr, char *title)
{
	printf("\n---%s---\n", title);
	for (int i = 0; arr[i]; i++)
		printf("%s\n", arr[i]);
	printf("-------\n");
}

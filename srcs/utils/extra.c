/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:02:06 by sting             #+#    #+#             */
/*   Updated: 2024/07/17 11:00:30 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_var_lst(t_var *var_lst)
{
	while (var_lst != NULL)
	{
		ft_printf("%s\n", var_lst->str);
		var_lst = var_lst->next;
	}
}

void	print_str_arr(char **arr, char *title)
{
	int	i;

	printf("\n---%s---\n", title);
	i = 0;
	while (arr[i])
		printf("%s\n", arr[i++]);
	printf("-------\n");
}

void print_redir_arr(t_redir **arr)
{
	int i = -1;

	if (!arr)
	{
		printf("redir_arr is NULL\n");
		return ;
	}
	printf(GREEN"=====Redir arr====="RESET"\n");
	while (arr[++i])
		printf("%s\n", arr[i]->filename);
}

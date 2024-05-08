
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:00:07 by sting             #+#    #+#             */
/*   Updated: 2024/04/18 15:08:32 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str_arr(char **str_arr)
{
	int	i;

	i = 0;
	if (str_arr == NULL)
	{
		ft_printf("str_arr is NULL when passed into free_str_arr()\n");
		exit(EXIT_FAILURE);
	}
	while (str_arr[i] != NULL)
	{
		free(str_arr[i]);
		i++;
	}
	free(str_arr);
}

void free_env_lst(t_env_var *list)
{
	t_env_var	*next;

	while (list != NULL)
	{
		next = list->next;
		free(list->str);
		free(list);
		list = next;
	}
}
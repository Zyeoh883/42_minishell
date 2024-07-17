/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:00:07 by sting             #+#    #+#             */
/*   Updated: 2024/07/17 11:21:33 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str_arr(char **str_arr)
{
	int	i;

	i = 0;
	if (str_arr == NULL)
		return ;
	while (str_arr[i] != NULL)
	{
		free(str_arr[i]);
		i++;
	}
	free(str_arr);
}

void	free_split(char **split)
{
	char	**head;

	if (!split)
		return ;
	head = split;
	while (*head != NULL)
	{
		free(*head);
		head++;
	}
	free(split);
}

void	free_lst(t_list *list)
{
	t_list	*next;

	while (list != NULL)
	{
		next = list->next;
		free(list->content);
		free(list);
		list = next;
	}
}

void	free_redir_arr(t_redir **arr)
{
	int	i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
	{
		free(arr[i]->filename);
		free(arr[i]);
	}
	free(arr);
}

void free_n_replace_str(char **str, char *replace)
{
	free(*str);
	*str = replace;
}

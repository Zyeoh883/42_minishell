/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:33:19 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/23 14:46:37 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void perror_and_exit(char *str, int exit_code)
{
    perror(str);
    exit(exit_code);
}

void free_split(char **split)
{
    char **head;

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

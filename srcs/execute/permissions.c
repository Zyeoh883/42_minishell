/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permissions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:08:49 by sting             #+#    #+#             */
/*   Updated: 2024/08/22 13:25:19 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	output_permissions(void)
{
	return (O_WRONLY | O_CREAT | O_TRUNC);
}

int	append_permissions(void)
{
	return (O_WRONLY | O_CREAT | O_APPEND);
}

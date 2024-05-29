/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_utils2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:14:12 by sting             #+#    #+#             */
/*   Updated: 2024/05/29 15:53:42 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int ft_strcasecmp(const char *s1, const char *s2)
{
	if (!s1 || !s1)
		return (-1);
	while (*s1 && *s2 && (ft_tolower(*s1) == ft_tolower(*s2)))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)(ft_tolower(*s1)) - (unsigned char)(ft_tolower(*s2)));
}
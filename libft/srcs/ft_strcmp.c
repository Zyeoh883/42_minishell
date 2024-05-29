/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<< HEAD:libft/srcs/ft_strcmp.c
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:03:47 by sting             #+#    #+#             */
/*   Updated: 2024/05/16 15:27:06 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
=======
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:14:12 by sting             #+#    #+#             */
/*   Updated: 2024/05/15 13:19:04 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int ft_strcasecmp(const char *s1, const char *s2)
{
	if (!s1 || !s1)
		return (-1);
	while (*s1 && *s2 && (ft_tolower(*s1) == ft_tolower(*s2)))
>>>>>>> dev:srcs/utils/z_utils2.c
	{
		s1++;
		s2++;
	}
<<<<<<< HEAD:libft/srcs/ft_strcmp.c
	return ((unsigned char)(*s1) - (unsigned char)(*s2));
}
=======
	return ((unsigned char)(ft_tolower(*s1)) - (unsigned char)(ft_tolower(*s2)));
}
>>>>>>> dev:srcs/utils/z_utils2.c

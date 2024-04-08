/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:29:21 by zyeoh             #+#    #+#             */
/*   Updated: 2023/10/20 17:09:06 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;

	str = NULL;
	while (*s)
	{
		if (*s == (unsigned char)c)
			str = (char *)s;
		s++;
	}
	if (*s == (unsigned char)c)
		str = (char *)s;
	return (str);
}

/*
if (!s)
	return (NULL);
*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:23:29 by zyeoh             #+#    #+#             */
/*   Updated: 2023/10/19 07:21:58 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	n;

	n = 0;
	while (*src && n + 1 < size)
	{
		*dest++ = *src++;
		n++;
	}
	if (n < size)
		*dest = '\0';
	while (*src++)
		n++;
	return (n);
}

/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	str1[] = "test";
	char	str2[] = "sssssss";
	int		n;

	n = strlcpy(str2, str1, -1);
	printf("%d\n%s\n", n, str2);
}
*/
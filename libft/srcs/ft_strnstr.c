/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:37:57 by zyeoh             #+#    #+#             */
/*   Updated: 2023/10/20 17:06:58 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = -1;
	if (!*needle)
		return ((char *)haystack);
	while (len > ++i && haystack[i] != '\0')
	{
		j = 0;
		while (needle[j] == haystack[i + j] && i + j < len && haystack[i + j])
			j++;
		if (needle[j] == '\0')
			return ((char *)haystack + i);
	}
	return (NULL);
}

	/*
	if (!haystack || !needle)
		return (NULL);
	*/
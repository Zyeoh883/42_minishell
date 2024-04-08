/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:43:45 by zyeoh             #+#    #+#             */
/*   Updated: 2023/10/20 14:52:57 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_checkset(char str, char const *set)
{
	int	n;

	n = -1;
	while (set[++n])
	{
		if (str == set[n])
			return (1);
	}
	return (0);
}

static void	ft_transfer(char *dest, const char *src, int len)
{
	while (--len >= 0)
	{
		dest[len] = src[len];
	}
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	start = -1;
	while (ft_checkset(s1[++start], set))
		;
	end = -1;
	while (s1[++end])
		;
	while (ft_checkset(s1[--end], set) && end > start)
		;
	end++;
	str = (char *)malloc(sizeof(char) * (end - start + 1));
	if (str == NULL)
		return (NULL);
	str[end - start] = '\0';
	ft_transfer(str, s1 + start, (end - start));
	return (str);
}

/*
#include <stdio.h>

int	main(void)
{
	char	*ptr;

	ptr = ft_strtrim("   xxx   xxx", " x");
	printf("%s\n", ptr);
	free (ptr);
}
*/
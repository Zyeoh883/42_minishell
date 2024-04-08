/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:25:55 by zyeoh             #+#    #+#             */
/*   Updated: 2023/10/20 17:08:37 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	string_count(const char *str, char c)
{
	int	word_count;

	word_count = 0;
	while (*str)
	{
		while (*str == c && *str)
			str++;
		if (*str != c && *str)
			word_count++;
		while (*str != c && *str)
			str++;
	}
	return (word_count);
}

static int	string_len(const char *str, char c)
{
	int	len;

	len = 0;
	while (str[len] != c && str[len])
		len++;
	return (len);
}

static void	str_cpy(char *dest, const char *src, int len)
{
	int	n;

	n = -1;
	while (++n < len)
		dest[n] = src[n];
	dest[n] = '\0';
}

char	**ft_split(const char *str, char c)
{
	char	**split;
	int		n;
	int		len;

	if (!str)
		return (NULL);
	split = (char **)malloc(sizeof(char *) * (string_count(str, c) + 1));
	if (!split)
		return (NULL);
	n = 0;
	while (*str)
	{
		if (*str != c && *str)
		{
			len = string_len(str, c);
			split[n] = (char *)malloc(sizeof(char) * (len + 1));
			str_cpy(split[n], str, len);
			n++;
			str += len - 1;
		}
		str++;
	}
	split[n] = 0;
	return (split);
}

/*
#include <stdio.h>

int	main(void)
{
	char	str[] = " hel pgo ikj";
	char	sep;
	char	**split;

	sep = ' ';
	split = ft_split(str, sep);
	while (*split != NULL)
	{
		printf("%s\n", *split);
		free (*split);
		split++;
	}
}
*/
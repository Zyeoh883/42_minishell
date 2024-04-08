/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 08:00:38 by zyeoh             #+#    #+#             */
/*   Updated: 2023/10/20 16:48:59 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		n;
	char	*str;

	if (!s)
		return (0);
	n = -1;
	while (s[start + ++n] && (size_t)n < len)
		;
	str = (char *)malloc(sizeof(char) * (n + 1));
	if (str == NULL)
		return (NULL);
	n = -1;
	while ((size_t)++n < len && s[n + start] && start <= sizeof(s) + 1)
		str[n] = s[n + start];
	str[n] = '\0';
	return (str);
}

/*
int	main(void)
{
	char	str[] = "testing12345";
	char	*ptr;

	ptr = ft_substr(str, 3, 20);
	write(1, ptr, 20);
	free (ptr);
}
*/
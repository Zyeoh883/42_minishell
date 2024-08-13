/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 08:00:38 by zyeoh             #+#    #+#             */
/*   Updated: 2024/06/12 10:11:28 by sting            ###   ########.fr       */
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
	while ((size_t)++n < len && s[n + start]
		&& start <= (unsigned int)ft_strlen(s) + 1)
		str[n] = s[n + start];
	str[n] = '\0';
	return (str);
}

/*
int	main(void)
{
	char	*ptr;

	char	str[] = "testing12345";
	ptr = ft_substr(str, 3, 20);
	write(1, ptr, 20);
	free (ptr);
}
*/
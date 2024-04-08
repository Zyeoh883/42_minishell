/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:39:23 by zyeoh             #+#    #+#             */
/*   Updated: 2023/10/20 14:50:43 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		n;

	if (!s || !f)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (str == NULL)
		return (0);
	n = -1;
	while (s[++n])
		str[n] = f(n, s[n]);
	str[n] = '\0';
	return (str);
}

/*
static char	ft_onlyz(unsigned int n, char c)
{
	c = 'z';
	if (n / 2 == 0)
		return (c);
	else
		return ('Z');
}

#include <stdio.h>

int	main(void)
{
	char	str[] = "testing";
	char	*result;

	result = ft_strmapi(str, ft_onlyz);
	printf("%s\n", result);
	free (result);
}
*/
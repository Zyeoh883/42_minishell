/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:05:52 by zyeoh             #+#    #+#             */
/*   Updated: 2023/10/20 16:56:38 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	n;

	if (!s || !f)
		return ;
	n = -1;
	while (s[++n])
		f(n, &s[n]);
}

/*
static void	ft_onlyz(unsigned int n, char *c)
{
	if (n / 2 == 0)
		*c = 'z';
	else
		*c = 'Z';
}

#include <stdio.h>

int	main(void)
{
	char	str[] = "testing";

	ft_striteri(str, ft_onlyz);
	printf("%s\n", str);
}
*/
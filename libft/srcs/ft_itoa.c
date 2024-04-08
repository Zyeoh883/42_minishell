/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:25:45 by zyeoh             #+#    #+#             */
/*   Updated: 2023/10/17 15:38:37 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	numlen(long n)
{
	if (n < 0)
		n *= -1;
	if (n / 10 > 0)
		return (1 + numlen(n / 10));
	return (1);
}

static void	recurcpy(char *str, long num)
{
	if (num < 0)
	{
		num *= -1;
		*str = '-';
		str++;
	}
	if (num == 0)
		return ;
	recurcpy(str, num / 10);
	str[numlen(num) - 1] = (num % 10) + '0';
}

char	*ft_itoa(int n)
{
	long	num;
	int		size;
	char	*str;

	num = (long)n;
	size = 0;
	if (num < 0)
		size++;
	size += numlen(num);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (0);
	str[size] = '\0';
	if (n == 0)
		str[0] = '0';
	recurcpy(str, num);
	return (str);
}

/*
#include <stdio.h>

int	main(void)
{
	int		n;
	char	*str;

	n = -2147483648;
	str = ft_itoa(n);
	printf("%s\n", str);
	free(str);
}
*/
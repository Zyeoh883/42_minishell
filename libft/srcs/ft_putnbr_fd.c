/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 07:05:20 by zyeoh             #+#    #+#             */
/*   Updated: 2023/10/18 07:22:33 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	num;
	char	buffer;

	num = (long)n;
	if (num < 0)
	{
		write(fd, "-", 1);
		num *= -1;
	}
	if (num / 10 > 0)
		ft_putnbr_fd(num / 10, fd);
	buffer = (num % 10) + '0';
	write(fd, &buffer, 1);
}

/*
int	main(void)
{
	int number = 42;
	ft_putnbr_fd(number, 1);
	return (0);
}
*/
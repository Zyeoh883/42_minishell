/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 07:02:28 by zyeoh             #+#    #+#             */
/*   Updated: 2023/10/20 10:44:18 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	n;

	if (!s)
		return ;
	n = -1;
	while (s[++n])
		;
	write(fd, s, n);
	write(fd, "\n", 1);
}

/*
int	main(void)
{
	ft_putendl_fd("testiung?", 1);
}
*/
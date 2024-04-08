/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:20:31 by zyeoh             #+#    #+#             */
/*   Updated: 2023/10/20 15:33:36 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*destptr;
	char	*srcptr;
	size_t	i;

	if (!dest && !src)
		return (NULL);
	destptr = (char *)dest;
	srcptr = (char *)src;
	i = -1;
	if (dest > src)
	{
		while (n-- > 0)
			destptr[n] = srcptr[n];
	}
	else
	{
		while (++i < n)
			destptr[i] = srcptr[i];
	}
	return (dest);
}

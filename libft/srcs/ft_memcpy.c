/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:19:37 by zyeoh             #+#    #+#             */
/*   Updated: 2023/10/20 17:03:52 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	void	*destptr;

	if (!dest && !src)
		return (NULL);
	destptr = dest;
	while (n-- > 0)
		*(char *)dest++ = *(char *)src++;
	return (destptr);
}

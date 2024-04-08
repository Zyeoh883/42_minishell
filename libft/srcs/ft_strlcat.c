/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:38:34 by zyeoh             #+#    #+#             */
/*   Updated: 2023/10/20 14:08:16 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	totallen;

	if ((!dest || !src) && !dstsize)
		return (0);
	dstlen = 0;
	srclen = 0;
	while (dest[dstlen] && dstlen < dstsize)
		dstlen++;
	while (src[srclen] != '\0')
		srclen++;
	if (dstlen >= dstsize)
		return (dstsize + srclen);
	totallen = dstlen + srclen;
	while (*src && (dstlen + 1) < dstsize)
	{
		dest[dstlen++] = *src++;
	}
	dest[dstlen] = '\0';
	return (totallen);
}

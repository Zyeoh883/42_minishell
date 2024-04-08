/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:34:19 by zyeoh             #+#    #+#             */
/*   Updated: 2023/10/22 15:58:53 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		n;
	int		index;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	n = 0;
	index = 0;
	while (s1[n])
		str[index++] = s1[n++];
	n = 0;
	while (s2[n])
		str[index++] = s2[n++];
	str[index] = '\0';
	return (str);
}

/*
int	main(void)
{
	char * s = ft_strjoin("tripouille", "42");
	printf("%s\n", s);
}
*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:06:42 by zyeoh             #+#    #+#             */
/*   Updated: 2023/10/22 15:58:50 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*end;

	if (!lst || !f || !del)
		return (NULL);
	result = NULL;
	while (lst)
	{
		end = ft_lstnew(f(lst->content));
		if (end)
		{
			end->next = NULL;
			ft_lstadd_back(&result, end);
			lst = lst->next;
		}
		else
			ft_lstclear(&result, del);
	}
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:41:07 by tcampbel          #+#    #+#             */
/*   Updated: 2023/11/16 10:43:48 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst1;
	t_list	*new;
	t_list	*temp;

	lst1 = NULL;
	while (lst)
	{
		if (f)
		{
			temp = (f)(lst->content);
			new = ft_lstnew(temp);
		}
		else
			return (NULL);
		if (!new)
		{
			(del)(temp);
			ft_lstclear(&lst1, del);
			return (NULL);
		}
		ft_lstadd_back(&lst1, new);
		lst = lst->next;
	}
	return (lst1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:56:47 by tcampbel          #+#    #+#             */
/*   Updated: 2023/11/14 18:21:27 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;
	t_list	*prev;

	if (!lst || !del)
		return ;
	current = *lst;
	while (current)
	{
		prev = current;
		current = current->next;
		del(prev->content);
		free (prev);
	}
	*lst = NULL;
}

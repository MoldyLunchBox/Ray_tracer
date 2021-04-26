/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 07:13:56 by amya              #+#    #+#             */
/*   Updated: 2019/04/08 07:50:22 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*ptr;

	if (!lst)
		return (NULL);
	new = (*f)(lst);
	ptr = new;
	while (lst->next)
	{
		new->next = (*f)(lst->next);
		new = new->next;
		lst = lst->next;
	}
	return (ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 01:25:14 by amya              #+#    #+#             */
/*   Updated: 2021/04/23 13:29:09 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;
	void	*cont;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	if (!content)
	{
		cont = NULL;
		new->content_size = 0;
		new->content = (void *)cont;
		new->next = NULL;
		return (new);
	}
	cont = malloc(content_size);
	if (!cont)
		return (NULL);
	new->content_size = content_size;
	ft_memcpy(cont, content, content_size);
	new->next = NULL;
	new->content = cont;
	return (new);
}

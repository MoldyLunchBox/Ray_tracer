/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramoukha <ramoukha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 20:51:49 by ramoukha          #+#    #+#             */
/*   Updated: 2019/05/24 02:06:32 by ramoukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!(str = malloc(size)))
		return (NULL);
	while (i < size)
	{
		str[i] = 0;
		i++;
	}
	return (void*)(str);
}

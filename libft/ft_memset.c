/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 20:43:10 by yoelguer          #+#    #+#             */
/*   Updated: 2019/04/18 00:04:42 by yoelguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *p, int c, size_t n_bytes)
{
	size_t	i;
	char	*p_mem;

	i = 0;
	p_mem = (char*)p;
	while (i < n_bytes)
	{
		p_mem[i] = c;
		i++;
	}
	return (p);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramoukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 07:24:29 by ramoukha          #+#    #+#             */
/*   Updated: 2019/05/11 07:27:52 by ramoukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char *rs1;
	const unsigned char *rs2;

	i = 0;
	rs1 = (unsigned char *)s1;
	rs2 = (unsigned char *)s2;
	if (s1 == s2 || n == 0)
		return (0);
	while (i < n && rs1[i] == rs2[i])
		i++;
	if (i == n)
		return (0);
	else
		return (rs1[i] - rs2[i]);
}

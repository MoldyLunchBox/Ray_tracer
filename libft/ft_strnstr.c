/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramoukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 19:05:01 by ramoukha          #+#    #+#             */
/*   Updated: 2019/05/19 05:54:32 by ramoukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	char	*tmp;
	char	*ret;

	if (n < ft_strlen(s1))
		tmp = ft_strsub(s1, 0, n);
	else
		tmp = ft_strdup(s1);
	ret = ft_strstr(tmp, s2);
	if (ret)
		ret = (char *)s1 + (ret - tmp);
	free(tmp);
	return (ret);
}

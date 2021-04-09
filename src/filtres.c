/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filtres.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 15:45:18 by amya              #+#    #+#             */
/*   Updated: 2021/04/01 14:18:24 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"
// t_vect		negative_filter(t_vect col)
// {
// 	col.x = 255 - col.x;
// 	col.y = 255 - col.y;
// 	col.z = 255 - col.z;
// 	return (col);
// }
void	filtre(t_all *rt)
{
	if (rt->filter == 1)
		ft_filter_mb(rt);
	if (rt->filter == 2)
		sepia_filtre(rt);
	// if (rt->filter == 3)
	// 	negative_filter(col);
}

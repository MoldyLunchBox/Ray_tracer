/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:51:42 by amya              #+#    #+#             */
/*   Updated: 2021/04/23 15:31:06 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

static void	x_bigger_thany(t_vect *ret, int *hold, t_vect *order)
{
	*hold = ret->y;
	ret->y = ret->x;
	ret->x = *hold;
	*hold = order->y;
	order->y = order->x;
	order->x = *hold;
}

static void	x_bigger_thanz(t_vect *ret, int *hold, t_vect *order)
{
	*hold = ret->z;
	ret->z = ret->x;
	ret->x = *hold;
	*hold = order->y;
	order->y = order->x;
	order->x = *hold;
}

static void	y_bigger_thanz(t_vect *ret, int *hold, t_vect *order)
{
	*hold = ret->z;
	ret->z = ret->y;
	ret->y = *hold;
	*hold = order->z;
	order->z = order->y;
	order->y = *hold;
}

static void	x_bigger_thanz2(t_vect *ret, int *hold, t_vect *order)
{
	*hold = ret->z;
	ret->z = ret->x;
	ret->x = *hold;
	*hold = order->z;
	order->z = order->x;
	order->x = *hold;
}

t_vect	sorting(t_vect in)
{
	t_vect	ret;
	int		hold;
	t_vect	order;

	order = (t_vect){1, 2, 3};
	ret = (t_vect){fabs(in.x), fabs(in.y), fabs(in.z)};
	if (ret.x > ret.y)
		x_bigger_thany(&ret, &hold, &order);
	if (ret.x > ret.z)
		x_bigger_thanz(&ret, &hold, &order);
	if (ret.y > ret.z)
		y_bigger_thanz(&ret, &hold, &order);
	if (ret.x > ret.z)
		x_bigger_thanz2(&ret, &hold, &order);
	return (order);
}

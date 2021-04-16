/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_malloc2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 15:53:43 by amya              #+#    #+#             */
/*   Updated: 2021/04/15 13:29:19 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

void	ft_alloc_obj2(t_obj **obj)
{
	(*obj)->radius = 0;
	(*obj)->radius2 = 0;
	(*obj)->size = 0;
	(*obj)->t = 0;
	(*obj)->type = 0;
	(*obj)->trans = 0;
	(*obj)->half_size = 0;
	(*obj)->refl = 0;
	(*obj)->name = NULL;
	(*obj)->surface = NULL;
	(*obj)->next = NULL;
}

void	ft_alloc_obj(t_obj **obj)
{
	(*obj) = (t_obj *)malloc(sizeof(t_obj));
	(*obj)->texture = ft_strdup(".");
	init_vect(&(*obj)->pos_slice, 0, 0, 0);
	init_vect(&(*obj)->a, 0, 0, 0);
	init_vect(&(*obj)->b, 0, 0, 0);
	init_vect(&(*obj)->c, 0, 0, 0);
	init_vect(&(*obj)->position, 0, 0, 0);
	init_vect(&(*obj)->text_modif, 0, 0, 0);
	init_vect(&(*obj)->slice, 0, 0, 0);
	init_vect(&(*obj)->translation, 0, 0, 0);
	init_vect(&(*obj)->rotation, 0, 0, 0);
	init_vect(&(*obj)->color, 0, 0, 0);
	init_vect(&(*obj)->axis, 0, 0, 0);
	init_vect(&(*obj)->hit, 0, 0, 0);
	init_vect(&(*obj)->norm, 0, 0, 0);
	init_vect(&(*obj)->direction, 0, 0, 0);
	ft_alloc_obj2(obj);
}

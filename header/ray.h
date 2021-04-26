/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:46:51 by amya              #+#    #+#             */
/*   Updated: 2021/04/23 16:46:55 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H
# include "vector.h"

typedef struct s_ray
{
	t_vect		origine;
	t_vect		direction;
}				t_ray;

void			init_ray(t_ray *r, t_vect origine, t_vect direc);

#endif

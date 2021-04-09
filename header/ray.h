/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:37:29 by yoelguer          #+#    #+#             */
/*   Updated: 2021/02/09 18:50:49 by yoelguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vector.h"

typedef struct	s_ray
{
	t_vect		origine;
	t_vect		direction;
}				t_ray;

void			init_ray(t_ray *r, t_vect origine, t_vect direc);

#endif

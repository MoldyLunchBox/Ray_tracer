/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:37:56 by yoelguer          #+#    #+#             */
/*   Updated: 2021/02/09 18:51:07 by yoelguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct	s_vect
{
	double		x;
	double		y;
	double		z;
}				t_vect;

typedef struct	s_vect_i
{
	int			x;
	int			y;
	int			z;
}				t_vect_i;

typedef struct	s_2d_d
{
	double		x;
	double		y;
}				t_2d_d;

typedef struct	s_2d_i
{
	int			x;
	int			y;
}				t_2d_i;

typedef struct	s_4d_i
{
	int			x;
	int			y;
	int			w;
	int			h;
}				t_4d_i;

void			normalize(t_vect *v);
void			zero_vect(t_vect *v);
void			init_vect(t_vect *v, double x, double y, double z);
double			get_norm_2(t_vect v);
double			vect_scal(t_vect v1, t_vect v2);
t_vect			new_vect(double x, double y, double z);
t_vect			trans_vect_xyz(t_vect v, t_vect tra);
t_vect			add_vect(t_vect v1, t_vect v2);
t_vect			sub_vect(t_vect v1, t_vect v2);
t_vect			mult_vect(t_vect v1, t_vect v2);
t_vect			vect_mult_val(t_vect v, double a);
t_vect			vect_div_val(t_vect v, double a);
t_vect			vect_div_val(t_vect v, double a);
t_vect			get_normalized(t_vect v);
t_vect			vect_cross(t_vect a, t_vect b);
t_vect			rot_vect_xyz(t_vect v, t_vect rot);

#endif

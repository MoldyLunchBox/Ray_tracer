/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 13:47:44 by amya              #+#    #+#             */
/*   Updated: 2021/04/26 11:20:30 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H
# include "ray.h"
# include "rt.h"
# include <SDL2/SDL.h>

typedef struct s_loop
{
	int			i;
	int			j;
	int			k;
}				t_loop;

typedef struct s_sol
{
	double				tmin;
	double				tmax;
}				t_sol;

typedef struct s_bb
{
	t_vect	min;
	t_vect	max;
	double	t1x;
	double	t2x;
	double	txmin;
	double	txmax;
	double	t1y;
	double	t2y;
	double	tymin;
	double	tymax;
	double	t1z;
	double	t2z;
	double	tzmin;
	double	tzmax;
	double	tmin;
	double	tmax;
}				t_bb;

typedef struct s_trns_parm
{
	t_vect		nm_trns;
	t_vect		tt;
	t_vect		tn;
	t_ray		ray_refr;
	t_vect		dir_refr;
	double		n1;
	double		n2;
	double		rad;
}				t_trns_parm;

typedef struct s_light
{
	t_vect				col;
	t_vect				ambi;
	t_vect				diff;
	t_vect				spec;
	t_vect				rm;
}				t_light;

typedef struct s_data_camera
{
	t_vect				pos;
	t_vect				dir;
	t_vect				u_dir;
	t_vect				v_dir;
	double				dist;
	double				focus_dis;
}				t_data_camera;

typedef struct s_data_light
{
	t_vect				position;
	t_vect				look_at;
	t_vect				dir;
	t_vect				color;
	double				intensity;
	t_ray				to_light;
	int					type;
	double				angle;
	double				ambient;
	t_vect				norm_light;
	struct s_data_light	*next;
}				t_data_light;
typedef union u_vect
{
	t_vect	order;
	double	tab[3];
}				t_uvect;

typedef struct s_4vects
{
	t_vect				one;
	t_vect				two;
	t_vect				three;
	t_vect				four;
}				t_4vects;

typedef struct s_faces
{
	t_vect				*node;
	struct s_plg		*next;
}				t_faces;

typedef struct s_plg
{
	t_vect				*vetrices;
	t_faces				*faces;
}				t_plg;

typedef struct s_uv
{
	double	u;
	double	v;
}				t_uv;

typedef struct s_obj
{
	int					id;
	char				*name;
	char				*texture;
	double				trans;
	double				refl;
	double				size;
	double				half_size;
	double				radius2;
	t_sol				(*inter)(struct s_obj *, t_ray);
	double				radius;
	double				t;
	t_sol				sol;
	double				type;
	double				length;
	t_vect				text_modif;
	t_vect				position;
	t_vect				translation;
	t_vect				rotation;
	t_vect				color;
	t_vect				axis;
	t_vect				slice;
	t_vect				pos_slice;
	t_vect				a;
	t_vect				b;
	t_vect				c;
	t_vect				hit;
	t_vect				norm;
	t_vect				direction;
	SDL_Surface			*surface;
	t_vect				color_copy;
	int					zero_one_to_skip;
	int					is_negative;
	int					disruption;
	struct s_obj		*next;
}				t_obj;

typedef struct s_event
{
	int					x;
	int					y;
}				t_event;

typedef struct s_all
{
	t_data_camera		*camera;
	t_data_light		*light;
	t_obj				*obj;
	SDL_Window			*win;
	SDL_Renderer		*rend;
	int					id;
	int					shadow;
	int					deep;
	int					aalias;
	int					orbit_angle;
	double				left;
	double				right;					
	int					filter;
	int					start;
	int					end;
	int					ren;
	t_event				event;
	t_vect				*screen_pixels;
}				t_all;

typedef struct s_find_closest
{
	t_obj		*pos;
	t_obj		*header;
	t_sol		t;
	double		t1;
}				t_find_closest;

typedef struct s_refraction
{
	t_ray		refracted_ray;
	double		n1;
	double		n2;
	double		r;
	t_vect		col;
	t_vect		ref_norm;
}				t_refraction;

typedef struct s_cone_top
{
	t_obj	plane;
	double	radius;
	t_sol	plan;
}				t_cone_top;

typedef struct s_cone_bottom
{
	t_obj	plane;
	double	radius;
	t_sol	plan;
}				t_cone_bottom;

#endif

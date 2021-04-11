/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramoukha <ramoukha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:37:09 by yoelguer          #+#    #+#             */
/*   Updated: 2021/04/11 11:39:21 by ramoukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include "ray.h"
# include "rt.h"
# include <SDL2/SDL.h>

typedef struct	s_loop
{
	int			i;
	int			j;
	int			k;
}				t_loop;

typedef struct	s_sol
{
	double				tmin;
	double				tmax;
}				t_sol;

typedef struct	s_bb
{
	t_vect min;
	t_vect max;
	double t1x;
	double t2x;
	double txmin;
	double txmax;
	double t1y;
	double t2y;
	double tymin;
	double tymax;
	double t1z;
	double t2z;
	double tzmin;
	double tzmax;
	double tmin;
	double tmax;
}				t_bb;

typedef struct	s_trns_parm
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

typedef struct	s_light
{
	t_vect				col;
	t_vect				ambi;
	t_vect				diff;
	t_vect				spec;
	t_vect				rm;
}				t_light;

typedef struct	s_data_camera
{
	t_vect				pos;
	t_vect				dir;
	t_vect				u_dir;
	t_vect				v_dir;
	double				dist;
	double				focus_dis;
}				t_data_camera;

typedef struct	s_data_light
{
	t_vect				position;
	t_vect				direction;
	t_vect				color;
	double				intensity;
	t_ray				to_light;
	int					type;
	double				angle;
	double				ambient;
	t_vect				norm_light;
	struct s_data_light	*next;
}				t_data_light;

typedef struct	s_faces
{
	t_vect				*node;
	struct s_plg		*next;
}				t_faces;

typedef struct	s_plg
{
	t_vect				*vetrices;
	t_faces				*faces;
}				t_plg;

typedef struct	s_obj
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

typedef struct	s_event
{
	int					x;
	int					y;
}				t_event;

typedef struct	s_all
{
	t_data_camera		*camera;
	t_data_light		*light;
	t_obj				*obj;
	SDL_Window			*win;
	SDL_Renderer		*rend;
	int					id;
	int					deep;
	int					aalias;
	int					filter;
	int					start;
	int					end;
	int					ren;
	t_event				event;
	t_vect				*screen_pixels;
}				t_all;

#endif

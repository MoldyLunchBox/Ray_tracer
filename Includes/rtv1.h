/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramoukha <ramoukha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 09:58:34 by ramoukha          #+#    #+#             */
/*   Updated: 2021/03/11 10:18:55 by ramoukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include <stdio.h>
# include <math.h>
# include <mlx.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "pthread.h"
# define WIDTH  1000
# define HEIGHT 1000
# define BPP 3
# define FILE_HEADER_SIZE 14
# define INFO_HEADER_SIZE 40
# include "math.h"

typedef	struct	s_sol
{
	double k;
	double a;
	double b;
	double c;
	double t1;
	double t2;
	double t;
	double tmp;
	double tmp_2;
	double tmp1;
	double delta;

}				t_sol;

typedef struct	s_vec
{
	double	x;
	double	y;
	double	z;
}				t_vec;

typedef	struct	s_var_light
{
	t_vec	l;
	t_vec	v;
	t_vec	dd;
	t_vec	rm;
	double	intensite_pixel;
	double	ang_norm_light;
}				t_var_light;

typedef	struct	s_camera
{
	double	low;
	t_vec	cam_dir;
	double	fov;
	t_vec	hotizontal;
	t_vec	up;
	t_vec	vertical;
	t_vec	low_left_corner;
	t_vec	look_from;
}				t_camera;
typedef struct	s_light
{
	t_vec		pos;
	t_vec		color;
	double		intens;

}				t_light;
typedef struct	s_sphere
{
	t_vec			pos;
	t_vec			trans;
	t_vec			rot;
	t_vec			color;
	double			radius;
	struct s_sphere	*next;
}				t_sphere;

typedef	struct	s_cone
{
	t_vec			pos;
	t_vec			trans;
	t_vec			axis;
	t_vec			rot;
	t_vec			color;
	char			*angle;
	struct s_cone	*next;
}				t_cone;

typedef	struct	s_cylinder
{
	t_vec				pos;
	t_vec				trans;
	t_vec				axis;
	t_vec				rot;
	t_vec				color;
	double				angle;
	struct s_cylinder	*next;
}				t_cylinder;

typedef	struct	s_delta{
	double	a;
	double	b;
	double	c;
	double	delta;
}				t_delta;

typedef	struct	s_ray
{
	t_vec o;
	t_vec dir;

}				t_ray;

typedef	struct	s_obj
{
	int				id;
	double			t;
	t_vec			hit;
	t_vec			pos;
	t_vec			trans;
	t_vec			axis;
	t_vec			rot;
	t_vec			n;
	t_vec			color;
	double			an_ra;
	double			(*inter)(t_ray *ray, struct s_obj *);
	struct s_obj	*next;
	double radius;
	double radius2;
	double k;
	t_vec v;


}				t_obj;

typedef	struct	s_hit
{
	double	t;
	t_obj	*o;
	t_vec	n;
	t_vec	p;
}				t_hit;

typedef	struct	s_mlx
{
	void		*ptr;
	void		*win;
	void		*img;
	void		*img_ptr;
	int			pxl;
	int			*d;

}				t_mlx;

typedef struct	s_vars
{
	t_vec	n;
	double	t;

}				t_vars;

typedef	struct	s_data
{
	char		**tab;
	double		t;
	t_vec		hit;
	t_vec		n;
	t_ray		shad;
	t_vars		var;
	int			fd;
	t_mlx		mlx;
	t_obj		*obj;
	t_camera	*camera;
	t_light		*light;
	t_ray		ray;
}				t_data;

typedef	struct	s_get_ray

{
	t_vec	horizontal;
	t_vec	vertical;
	t_vec	cam_u;
	t_vec	cam_v;
	t_vec	cam_w;
	t_ray	new;
	double	half_h;
	double	half_w;
}				t_get_ray;
typedef	struct	s_raytracer

{
	t_vec	color;
	t_obj	*head;
	t_obj	*save;
	t_ray	shadow;
	int		y;
	int		x;
	double	t;
	double	t1;
}				t_raytracer;

typedef	struct	s_split_data
{
	int		i;
	char	**ar;
	int		j;
	int		dot;
	t_vec	ret;
}				t_split_data;
double	intersection_paraploid(t_ray *r, t_obj *p);
double				intersection_ellipsoid(t_ray *r, t_obj *e);
double			get_closest(t_data *data, int x, int y, t_obj **save);
t_vec			split_data(t_data *data, char *str);
void			color_limit(t_vec *color);
double			ntersection_spher(t_ray *r, t_obj *s);
void			get_shadow(t_obj *head, t_obj *s, t_data *data, t_vec *col);
void			ray_tracer(t_data *data);
double			cone_intersection(t_ray *ray, t_obj *cone);
t_vec			ft_object_normal(double hit, t_ray *ray, t_vec p, t_obj *o);
int				ft_lines(int fd);
double			get_norm(t_vec v);
t_vec			normal_sphere(double t, t_ray r, t_sphere s);
t_vec			normalize(t_vec vec);
int				mouse_move(int x, int y, t_data *data);
double			ft_min_ray(double t1, double t2, double t);
double			ft_atof(char *str);
void			free_2d(char **tab);
t_vec			light_it_up(t_data *data, int x, int y, t_obj *obj);
void			init_data(t_data **data, char *av);
t_var_light		*ft_var_light(t_data *data, t_obj *obj, t_var_light *light);
double			intersect_cone(t_ray *r, t_obj *c);
double			intersect_plane(t_ray *r, t_obj *plane);
double			ft_min_ray(double t1, double t2, double t);
double			intersection_spher(t_ray *r, t_obj *s);
double			get_norm(t_vec v);
int				keyhook(int key, t_data *data);
void			image_clear(int *d);
void			call_error(t_data *data);
int				ft_checker(t_data **data);
void			camera_check(t_data **dat, int i);
void			light_check(t_data **dat, int i, int light);
void			obj_check(t_data **dat, int i, int id);
double			ft_atof(char *str);
t_obj			*add_node(t_data **dat);
void			init_data(t_data **data, char *av);
t_ray			get_ray(double u, double v, t_camera *camera);
t_vec			get_camera_direction(t_camera cam, t_vec get_ray);
t_ray			init_rayy(int i, int j, t_camera *cam);
t_vec			get_color(t_data *data, t_obj *obj, int x, int y);
double			intersection_cylinder(t_ray *ray, t_obj *cylinder);
t_vec			vec_cross(t_vec v1, t_vec v2);
t_vec			vec_add(t_vec v1, t_vec v2);
t_ray			get_ray(double u, double v, t_camera *camera);
void			ft_camera(t_camera *cam, t_vec vup, double aspect);
t_vec			get_camera_direction(t_camera cam, t_vec get_ray);
t_vec			ft_rotate_x(t_vec v, double angle);
t_vec			ft_rotate_y(t_vec v, double angle);
t_vec			ft_rotate_z(t_vec v, double angle);
t_vec			ft_rotate(t_vec v, t_vec rot);
t_vec			ft_translate(t_vec v, t_vec trans);
t_vec			ft_transform_ray(t_obj *o);
int				ft_close(t_data *data);
t_vec			vec_sub(t_vec v1, t_vec v2);
double			dot_product(t_vec v1, t_vec v2);
t_vec			normal_sphere(double t, t_ray r, t_sphere s);
t_vec			normalize(t_vec vec);
t_vec			vec_product(t_vec v, double i);
t_vec			split_data(t_data *data, char *str);
int				error_check(char **ar, t_data *data);
void			free_list(t_obj *obj);
int				init_obj(t_obj *temp, int i, t_data *data, int id);
int				str_isnum(char *tab);

#endif

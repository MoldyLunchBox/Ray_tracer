/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:37:40 by yoelguer          #+#    #+#             */
/*   Updated: 2021/04/15 17:20:48 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# define WIN_W       1200
# define WIN_H       1200
# define NBR_RAYS    40
# define PI          3.14159265359
# include "vector.h"
# include <pthread.h>
# include "ray.h"
# include "data.h"
# include "../libft/libft.h"
# include <stdio.h>
# include "SDL2/SDL.h"
# include "SDL2/SDL_image.h"
# include "vector.h"
# include <math.h>

int			s_box(char **table, int i, t_all *data, t_obj *box);
void		threading(t_all alll);
void		cartoon_filter(t_all *rt);
void		ft_filter_mb(t_all *rt);
void		sepia_filtre(t_all *rt);
void		filtre(t_all *rt);
int			light_direct(t_all data, t_ray ray);
t_vect		ft_refraction(t_obj *pos, t_all data, t_ray ray, int nbrbonds);
t_vect		ft_reflection(t_obj *pos, t_all data, t_ray ray, int nbrbonds);
t_vect		rend_pix(t_all data, t_ray ray, int nbrbonds);
int			ft_val(char *str);
int			ft_val2(char *str);
int			ft_camera(char **table, t_all *data);
int			ft_obj(char **table, t_all *data);
int			check_str2(char **str, int j, int k);
int			f_str(char **str, int j, int k);
int			check_str1(char **str, int j, int k);
int			f_str2(char **str, int j, int d);
int			ft_cylinder(char **table, t_all *data);
int			ft_light(char **table, t_all *data);
int			file_checker(char *str, t_all *data);
int			s_sphere(char **table, int i, t_all *data, t_obj *sphere);
int			s_plane(char **table, int i, t_all *data, t_obj *plane);
int			s_cone(char **table, int i, t_all *data, t_obj *cone);
int			s_ring(char **table, int i, t_all *data, t_obj *ring);
int			s_cylinder(char **table, int i, t_all *data, t_obj *cyl);
int			s_triangle(char **table, int i, t_all *data, t_obj *tri);
int			s_paraploid(char **table, int i, t_all *d, t_obj *par);
int			s_ellipsoid(char **table, int i, t_all *data, t_obj *el);
int			s_cube(char **table, int i, t_all *data, t_obj *cube);
void		loop_program(t_all *data);
void		init_sdl(t_all *data);
void		ft_lstdel(t_obj **alst);
void		sdl_error(char *message);
void		ft_alloc_light(t_data_light **light);
void		ft_alloc_obj(t_obj **obj);
void		*raytracing(void *data);
void		ft_free_obj(t_all *data);
void		init_li(t_light *li, t_data_light *ligth, t_obj *obj, t_ray ray);
t_vect		light_obj(t_obj *obj, t_all data, t_ray ray, double t);
t_vect 		on_shadow(t_obj *pos, t_all data, t_ray ray, t_vect col);
t_ray		init_rayy(t_2d_i var, t_data_camera *cam, t_2d_d d, t_2d_d p);
double		find_obj_scnd(t_all data, t_ray ray, t_ray to_light, t_obj *pos);
double		ft_atof(char *str);
void		texturing(t_obj *obj);
t_sol		find_solution(double delta, t_vect abc);
t_sol		intersection_ray_sphere(t_obj *obj, t_ray r);
t_sol		intersection_ray_ring(t_obj *obj, t_ray r);
t_sol		intersection_ray_plan(t_obj *obj, t_ray r);
t_sol		intersection_ray_cylindre(t_obj *obj, t_ray r);
t_sol		intersection_ray_cone(t_obj *cone, t_ray r);
t_sol		intersection_ray_geometry(t_obj *gem, t_ray r);
t_sol		intersection_paraploid(t_obj *para, t_ray r);
t_sol		intersection_ellipsoid(t_obj *eli, t_ray r);
t_sol		intersection_cube(t_obj *box, t_ray r);
double		get_length(t_vect u);
t_vect		safe_color(t_vect p);
int			inside_rect(t_all *data, SDL_Rect r);
void		init_2d_vect(t_2d_d *v);
t_2d_i		plane_uv(t_obj *obj, t_2d_i size);
t_2d_i		sphere_uv(t_obj *obj, t_2d_i size);
t_2d_i		uv_mapping_cyl_cone(t_obj *obj, t_2d_i size);
void		sdl_set_text(char *txt, t_vect_i col, t_4d_i rect, t_all *data);
t_ray		new_ray(int i, int j, t_all data);
void		event_alias(t_all *data);
void		event_filter(t_all *data);
void		event_focus(t_all *data);
void		event_go(t_all *data);
double		comp(double x, double y, double z);
void		cone_norm(t_obj *cone, t_ray r, double t);
int			space_counter(char *str);
void        free_2d(char ***str);
int         white_split_check(char **str);
int         info_checker(char **str);
int		    checker_loop(char ***str, char *table, int j, int max_vects);
void		f_limited_cylinder2(char **str, int j, t_obj *cylinder);
void		f_limited_cylinder(char **str, int j, t_obj *cylinder);
int			s_limited_cylinder(char **table, int i, t_all *data, t_obj *cyl);
t_sol		intersection_ray_limited_cylindre(t_obj *cyl, t_ray r);
t_sol intersection_box(t_obj *box, t_ray ray);
t_vect		norm_cube(t_obj *box, t_vect hit_point);
t_vect			sorting(t_vect in);
int         space_counter(char *str);
int         ft_lines_in_file(char *str);

#endif

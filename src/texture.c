/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amya <amya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 16:54:18 by amya              #+#    #+#             */
/*   Updated: 2021/04/23 16:12:08 by amya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rt.h"

t_uv	get_plane_uv(t_obj *plane, t_2d_i size)
{
	t_uv	uv;
	t_vect	u;
	t_vect	v;

	u = (t_vect){plane->norm.y, -plane->norm.z, plane->norm.x};
	v = vect_cross(plane->norm, u);
	uv.u = vect_scal(u, plane->hit) * 0.01;
	uv.v = vect_scal(v, plane->hit) * 0.01;
	uv.u = (uv.u - floor(uv.u)) * size.x;
	uv.v = (uv.v - floor(uv.v)) * size.y;
	return (uv);
}

t_uv	get_uv(t_obj *obj, t_2d_i size)
{
	t_uv	uv;

	if (ft_strcmp(obj->name, "sphere") == 0)
		uv = sphere_uv(obj, size);
	if (ft_strcmp(obj->name, "cylinder") == 0)
		uv = uv_mapping_cyl_cone(obj, size);
	if (ft_strcmp(obj->name, "cone") == 0)
		uv = uv_mapping_cyl_cone(obj, size);
	if (ft_strcmp(obj->name, "plane") == 0)
		uv = get_plane_uv(obj, size);
	return (uv);
}

int	init_bpp(unsigned char **pos, int bpp, t_obj *obj)
{
	t_2d_i	size;
	t_uv	tex;

	bpp = obj->surface->format->BytesPerPixel;
	size.x = obj->surface->w;
	size.y = obj->surface->h;
	tex = get_uv(obj, size);
	*pos = (unsigned char *)obj->surface->pixels
		+ ((int)(tex.v + obj->text_modif.y) *obj->surface->pitch
			+ (int)(tex.u + obj->text_modif.x) *bpp);
	return (bpp);
}

void	texturing(t_obj *obj)
{
	int					bpp;
	int					pix;
	SDL_Color			rgb;
	unsigned char		*pos;

	pix = -1;
	bpp = 0;
	bpp = init_bpp(&pos, bpp, obj);
	if (bpp == 1)
		pix = *pos;
	else if (bpp == 2)
		pix = *(unsigned short *)pos;
	else if (bpp == 3)
	{
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			pix = pos[0] << 16 | pos[1] << 8 | pos[2];
		else
			pix = pos[0] | pos[1] << 8 | pos[2] << 16;
	}
	else if (bpp == 4)
		pix = *(unsigned int *)pos;
	SDL_GetRGB(pix, obj->surface->format, &rgb.r, &rgb.g, &rgb.b);
	obj->color.x = rgb.r;
	obj->color.y = rgb.g;
	obj->color.z = rgb.b;
}

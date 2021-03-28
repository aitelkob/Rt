/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 13:56:42 by babdelka          #+#    #+#             */
/*   Updated: 2021/03/28 13:58:42 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				texture_help(t_rtv *rtv, t_object *obj, t_vector point,\
t_txtemp *txt)
{
	if (obj->type == PLANE)
	{
		txt->x = fmod((-obj->origin.x - rtv->translationx + point.x) /\
		rtv->scale, 1);
		txt->y = fmod((-obj->origin.z - rtv->translationy + point.z) /\
		rtv->scale, 1);
	}
	else if (obj->type == SPHERE)
	{
		txt->x = (1 - ((atan2((obj->origin.x - point.x), -obj->origin.z +\
		point.z) / (2.0 * PI)))) + fabs(rtv->translationx / obj->radius);
		txt->y = 1 - (acos((((obj->origin.y - point.y)) / (obj->radius))))\
		/ PI + fmod(rtv->translationy, obj->radius) / obj->radius;
	}
	else if (obj->type == CYLINDER || obj->type == CONE)
	{
		txt->x = (1 - (atan2((-obj->origin.x + point.x), (-obj->origin.z +\
		point.z))) / (2.0 * PI)) + fabs(rtv->translationx / rtv->scale);
		txt->y = fmod((point.y) / rtv->scale, 1) + rtv->translationy /\
		rtv->scale;
	}
}

t_vector			texture_noise(double x, double y, t_vector color)
{
	x = floor(x * 6);
	y = floor(y * 6);
	if (fmod(x + y, 2) == 0)
		return (t_vector){0, 0, 0};
	else
		return (color);
}

t_vector			texture_noise_sine(double x, double y)
{
	t_vector		color;
	double			tetha;

	tetha = (5.0 * (x < 0 ? 1 + x : x)) /\
	(3.0 * (y < 0 ? 1 + y : y)) + PI / 2.0;
	color.x = sin(tetha) * 192 + 128;
	color.x = max(0, min(255, color.x));
	color.y = sin(tetha - (2.0 * PI) / 3.0) * 192 + 128;
	color.y = max(0, min(255, color.y));
	color.z = sin(tetha - (4.0 * PI) / 3.0) * 192 + 128;
	color.z = max(0, min(255, color.z));
	return (color);
}

t_vector			texture_fromfile(t_rtv *rtv, t_object *obj,\
t_vector point, t_txtemp txt)
{
	int ipos;

	txt.x = (txt.x < 0 ? 1 + txt.x : txt.x) * (obj->w);
	txt.y = (txt.y < 0 ? 1 + txt.y : txt.y) * (obj->h);
	ipos = 4 * obj->w * (int)txt.y + (int)txt.x * 4;
	if (ipos < 4 * obj->img_texture->width * obj->img_texture->height\
	&& ipos >= 0)
	{
		return ((t_vector) {
			png_to_rgb(obj->img_texture->buffer[ipos + 2]),
			png_to_rgb(obj->img_texture->buffer[ipos + 1]),
			png_to_rgb(obj->img_texture->buffer[ipos])});
	}
	return (obj->color);
}

t_vector			texture(t_rtv *rtv, t_object *obj, t_vector point)
{
	t_txtemp		txt;
	int				cond;
	int				concylinder;

	txtinit(&txt);
	texture_help(rtv, obj, point, &txt);
	cond = obj->type == PLANE ? point.x > obj->origin.x + rtv->translationx\
	&& point.x < obj->origin.x + rtv->translationx + rtv->scale &&\
	point.z > obj->origin.z + rtv->translationy && point.z < obj->origin.z +\
	rtv->translationy + rtv->scale : 1;
	concylinder = obj->type == CONE || obj->type == CYLINDER ? point.y >\
	obj->origin.y + rtv->translationy && point.y < obj->origin.y +\
	rtv->translationy + rtv->scale : 1;
	if (obj->disruptions == CHECK)
		return (texture_noise(txt.x, txt.y, obj->color));
	else if (obj->disruptions == DISRUPT)
		return (texture_noise_sine(txt.x, txt.y));
	else if (obj->disruptions == PERLIN)
		return (multi(obj->color, perlin2d((txt.x < 0 ? -txt.x : txt.x),\
		(txt.y < 0 ? -txt.y : txt.y), 100, 4)));
	else if (obj->w != -1 && ((concylinder && cond) || obj->type == SPHERE))
		return (texture_fromfile(rtv, obj, point, txt));
	return (obj->color);
}
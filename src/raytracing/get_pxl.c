/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pxl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 10:02:17 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/19 17:54:55 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double				get_dest(t_rtv *rtv, t_ray ray,
t_object **close, t_object *current)
{
	t_object		*tmp;
	double			dst;
	double			min;

	min = -1;
	tmp = rtv->obj;
	while (tmp)
	{
		if (tmp->type == SPHERE)
			dst = intersection_sphere(ray, *tmp);
		else if (tmp->type == PLANE)
			dst = intersection_plane(ray, *tmp);
		else if (tmp->type == CYLINDER)
			dst = intersection_cylinder(ray, *tmp);
		else if (tmp->type == CONE)
			dst = intersection_cone(ray, *tmp);
		if (dst > 0 && (dst < min + 0.1 || min == -1))
		{
			*close = tmp;
			min = dst;
		}
		tmp = tmp->next;
	}
	if (current != NULL && *close == current)
		return (-1);
	return (min);
}

t_vector			obj_norm(t_ray ray, t_object *obj, double dst)
{
	double			m;
	double			tk;
	t_vector		normal;
	t_vector		p_c;
	t_vector		xvec;

	xvec = sub(ray.origin, obj->origin);
	if (obj->type != PLANE && obj->type != SPHERE)
		m = dot(ray.direction, obj->aim) * dst + dot(xvec, obj->aim);
	if (obj->type != PLANE)
		p_c = add(xvec, multi(ray.direction, dst));
	tk = 1 + tan(deg_to_rad(60) / 2) * tan(deg_to_rad(60) / 2);
	if (obj && obj->type == SPHERE)
		normal = p_c;
	else if (obj && obj->type == PLANE)
		normal = multi(obj->aim, -1);
	else if (obj && obj->type == CYLINDER)
		normal = sub(p_c, multi(obj->aim, m));
	else if (obj && obj->type == CONE)
		normal = sub(p_c, multi(obj->aim, tk * m));
	if (dot(ray.direction, normal) > 0)
		normal = multi(normal, -1);
	return (nrm(normal));
}

void				initgp(t_object *obj, t_vector color, t_vector colorini)
{
	obj = NULL;
	color = (t_vector){0, 0, 0};
	colorini = (t_vector){0, 0, 0};
}

t_vector			get_pxl(t_rtv *rtv, t_ray ray)
{
	t_hit			hit;
	t_object		*obj;
	t_vector		color;
	t_vector		colorini;
	double			ratio[2];

	hit.depth = 30;
	initgp(obj, color, colorini);
	if ((hit.dst = get_dest(rtv, ray, &obj, NULL)) <= 0)
		return (color);
	hit.point = add(ray.origin, multi(ray.direction, hit.dst));
	if (hit.dst > 0)
		colorini = obj->color;
	ratio[0] = obj->reflection + 0.2;
	ratio[1] = obj->refraction + 0.2;
	if (rtv->light)
		colorini = lighting(rtv, obj, hit, ray);
	if (hit.depth > 0)
		color = reflectandrefract(ray, obj, rtv, hit);
	color = divi(finalcolor(colorini, color, ratio), 5);
	return (color);
}

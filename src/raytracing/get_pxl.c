/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pxl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 10:02:17 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/10 11:07:02 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double				get_dest(t_rtv *rtv, t_ray ray,
t_object **close, t_object *current)
{
	t_object		*tmp;
	double			dst;

	tmp = rtv->obj;
	rtv->hit.dst = -1;
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
		if (dst > 0 && (dst < rtv->hit.dst + 0.000001 || rtv->hit.dst == -1))
		{
			*close = tmp;
			rtv->hit.dst = dst;
		}
		tmp = tmp->next;
	}
	rtv->hit.point = add(ray.origin, multi(ray.direction, rtv->hit.dst));
	if (current != NULL && *close == current)
		return (-1);
	return (rtv->hit.dst);
}

t_object			*obj_norm(t_ray ray, t_object *obj, double dst)
{
	double			m;
	double			tk;
	t_vector		normal;
	t_vector		p_c;
	t_vector		xvec;

	xvec = vecto_subvec(ray.origin, obj->origin);
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
	obj->normal = nrm(normal);
	return (obj);
}

t_vector			get_pxl(t_rtv *rtv, t_ray ray)
{
	t_object		*obj;
	t_vector		color;
	t_object		*current;

	obj = NULL;
	current = NULL;
	color = (t_vector){0, 0, 0};
	if (!(get_dest(rtv, ray, &obj, current)))
		return (color);
	// rtv->hit.hit = add(ray.origin, multi(ray.direction, rtv->hit.dst));
	color = effect(*rtv, ray, obj);
	// if (rtv->hit.dst > 0)
	// 	color = multi(obj->color, 0.1);
	color = multi(color, 0.55);
	if (rtv->light)
		color = add(color, lighting(rtv, obj_norm(ray, obj, rtv->hit.dst), rtv->hit.point, ray));
	return (color);
}

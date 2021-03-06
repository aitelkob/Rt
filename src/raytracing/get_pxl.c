/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pxl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selibrah <selibrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 10:02:17 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/28 15:13:17 by selibrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_quadratic			intersection(t_ray ray, t_object tmp)
{
	t_quadratic		q;

	q.t0 = 0;
	if (tmp.type == SPHERE)
		q = intersection_sphere(ray, tmp);
	else if (tmp.type == PLANE)
	{
		q.t0 = intersection_plane(ray, tmp);
		q.t1 = -1;
	}
	else if (tmp.type == TRIANGLE)
		q.t0 = intersection_triangle(ray, tmp);
	else if (tmp.type == CYLINDER)
		q = intersection_cylinder(ray, tmp);
	else if (tmp.type == CONE)
		q = intersection_cone(ray, tmp);
	return (q);
}

double				get_dest(t_rtv *rtv, t_ray ray,
t_object **close, t_object *current)
{
	t_object		*tmp;
	double			min;
	t_quadratic		q;

	min = -1;
	tmp = rtv->obj;
	while (tmp)
	{
		if (tmp != current || ray.type == 1)
		{
			q = intersection(ray, *tmp);
			q.t0 = slice(ray, q, rtv->slice, tmp);
			if (q.t0 > 0 && (q.t0 < min + 0.000000001 ||\
				min == -1) && tmp->negative != 1)
			{
				min = negativeobj(rtv, ray, q, min);
				*close = tmp;
			}
		}
		tmp = tmp->next;
	}
	if (current != NULL && *close == current)
		return (-1);
	return (min);
}

t_vector			obj_norm(t_ray ray, t_object *ob, double dst)
{
	double			m;
	t_vector		normal;
	t_vector		p_c;
	t_vector		xvec;

	normal = (t_vector){0, 0, 0};
	xvec = sub(ray.origin, ob->origin);
	if (ob->type != PLANE && ob->type != SPHERE)
		m = dot(ray.direction, ob->aim) * dst + dot(xvec, ob->aim);
	if (ob->type != PLANE)
		p_c = add(xvec, multi(ray.direction, dst));
	if (ob && ob->type == SPHERE)
		normal = p_c;
	else if (ob && ob->type == PLANE)
		normal = multi(ob->aim, -1);
	else if (ob && ob->type == CYLINDER)
		normal = sub(p_c, multi(ob->aim, m));
	else if (ob && ob->type == CONE)
		normal = sub(p_c, multi(ob->aim, (1 + tan(deg_to_rad(60) /
		2) * tan(deg_to_rad(60) / 2)) * m));
	else if (ob && ob->type == TRIANGLE)
		normal = crossproduct(sub(ob->c1, ob->origin), sub(ob->c2, ob->origin));
	if (dot(ray.direction, normal) > 0)
		normal = multi(normal, -1);
	return (nrm(normal));
}

void				init_get_pxl(t_rtv *rtv, t_ray *ray,
t_hit *hit, t_vector *color)
{
	hit->depth = rtv->camera->depth;
	color[0] = (t_vector){0, 0, 0};
	color[1] = (t_vector){250, 0, 0};
	ray->type = 0;
}

t_vector			get_pxl(t_rtv *rtv, t_ray ray)
{
	t_hit			hit;
	t_object		*obj;
	t_vector		color[2];
	double			ratio[2];

	init_get_pxl(rtv, &ray, &hit, color);
	if ((hit.dst = get_dest(rtv, ray, &obj, NULL)) <= 0)
		return (color[0]);
	hit.point = add(ray.origin, multi(ray.direction, hit.dst));
	hit.color = texture(rtv, obj, hit.point);
	if (hit.dst > 0 && rtv->light->intensity == 0)
		color[0] = multi(divi(hit.color, 100), rtv->camera->amblgt);
	ratio[0] = obj->reflection + 0.2;
	ratio[1] = obj->refraction + 0.2;
	if (rtv->light && rtv->light->intensity != 0)
	{
		color[0] = lighting(rtv, obj, hit, ray);
		if (hit.depth > 0)
			color[1] = reflectandrefract(ray, obj, rtv, hit);
		color[1] = divi(finalcolor(color[0], color[1], ratio), 5);
	}
	else
		return (color[0]);
	return (color[1]);
}

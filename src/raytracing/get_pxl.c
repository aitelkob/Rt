/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pxl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 10:02:17 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/24 19:15:59 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double slice(t_ray ray, t_quadratic q, t_slice *slice, t_object *obj)
{
	t_vector		xvec;
	t_vector		p_c;
	double		is_sliced;
	t_slice 	*tmp;

	tmp = slice;
	is_sliced = q.t0;
	while (tmp)
	{
		if (tmp->shape == obj->slicing)
		{
			xvec = sub(ray.origin, tmp->origin);
			p_c = add(xvec, multi(ray.direction, q.t0));
			is_sliced = dot(p_c, tmp->vec) > 0 ? q.t0 : -1;
			if(is_sliced < 0)
			{
				p_c = add(xvec, multi(ray.direction, q.t1));
				is_sliced = dot(p_c, tmp->vec) > 0 ? q.t1 : -1;;
			}
		}
		tmp = tmp->next;
	}
	
	return is_sliced;
}

t_quadratic			intersection(t_ray ray, t_object tmp)
{
	t_quadratic		q;

	q.t0 = 0;
	if (tmp.type == SPHERE)
		q = intersection_sphere(ray, tmp);
	else if (tmp.type == PLANE)
		q.t0 = intersection_plane(ray, tmp);
	else if (tmp.type == TRIANGLE)
		q.t0 = intersection_triangle(ray, tmp);
	else if (tmp.type == CYLINDER)
		q = intersection_cylinder(ray, tmp);
	else if (tmp.type == CONE)
		q = intersection_cone(ray, tmp);
	return (q);
}

int					isnegativeobj(t_rtv *rtv, t_ray ray, double dst)
{
	t_object		*tmp;
	t_quadratic		q;

	tmp = rtv->obj;
	while (tmp)
	{
		if (tmp->negative == 1)
		{
			q = intersection(ray, *tmp);
			if ((dst > q.t0 && dst < q.t1))
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
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
		q = intersection(ray, *tmp);
		q.t0 = slice(ray, q, rtv->slice, tmp);
		if (q.t0 > 0 && (q.t0 < min + 0.000000001 ||\
		min == -1) && tmp->negative != 1)
			if ((isnegativeobj(rtv, ray, q.t0) ||\
			(isnegativeobj(rtv, ray, q.t1) && tmp->type != PLANE)))
			{
				if (isnegativeobj(rtv, ray, q.t0))
					min = q.t0;
				else
					min = q.t1;
				*close = tmp;
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

	normal = (t_vector){0, 0, 0};
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
	else if (obj && obj->type == TRIANGLE)
		normal = crossproduct(sub(obj->c1, obj->origin), sub(obj->c2, obj->origin));
	if (dot(ray.direction, normal) > 0)
		normal = multi(normal, -1);
	return (nrm(normal));
}


double maptex(double x)
{
	return fmod(x ,1000);
}
t_vector texture(t_rtv *rtv, t_object *obj, t_vector point)
{
	double x = 0;
	double y = 0;
	int ipos = 0;
	double scale =50;

	int cond = obj->type == PLANE ? point.z > 0  + obj->origin.z - scale / 2.0
	    && point.z < scale / 2.0 + obj->origin.z: point.y > 0  + obj->origin.y - scale / 2.0
	    && point.y < scale / 2.0 + obj->origin.y;
	if(obj->type == PLANE)
	{	
		x = fmod((obj->origin.x - scale / 2.0 + point.x)/ scale,1);
		y = fmod((obj->origin.z - scale / 2.0 + point.z)/ scale,1);
	}
	else if(obj->type == SPHERE)
	{	
		x = (1 - ((atan2((obj->origin.x - point.x), obj->origin.z - point.z) / (2.0 * PI))));
		y = ((1 - (acos((((obj->origin.y - point.y))/ (obj->radius)))) / PI));
	}
	else if(obj->type == CYLINDER || obj->type == CONE)
	{	
		x = (1 - (atan2(-obj->origin.x + point.x, -obj->origin.z + point.z)) / (2.0 * PI));
		y = fmod((-obj->origin.y + point.y)/scale, 1);
	}

	x = (x < 0 ? fabs(x) : x) * (1000);
	y = (y < 0 ? fabs(y) : y) * (1000);

	ipos = 4 * 1000 * (int) y + (int) x  * 4;
	if(	   point.x > 0  + obj->origin.x - scale / 2.0 
		&& point.x < scale / 2.0 + obj->origin.x
	    && cond)
		return (t_vector) {
			rtv->mlx.img_texture->buffer[ipos+2] < 0 ? 255 + rtv->mlx.img_texture->buffer[ipos+2] : rtv->mlx.img_texture->buffer[ipos+2],
			rtv->mlx.img_texture->buffer[ipos+1] < 0 ? 255 + rtv->mlx.img_texture->buffer[ipos+1] : rtv->mlx.img_texture->buffer[ipos+1],
			rtv->mlx.img_texture->buffer[ipos]   < 0 ? 255 + rtv->mlx.img_texture->buffer[ipos+2] : rtv->mlx.img_texture->buffer[ipos]};
	return obj->color;
}

t_vector			get_pxl(t_rtv *rtv, t_ray ray)
{
	t_hit			hit;
	t_object		*obj;
	t_vector		color[2];
	double			ratio[2];

	hit.depth = rtv->camera->depth;
	color[0] = (t_vector){0, 0, 0};
	color[1] = (t_vector){0, 0, 0};
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

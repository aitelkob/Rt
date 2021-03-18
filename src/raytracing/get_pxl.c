/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pxl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 10:02:17 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/18 12:34:44 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double				get_dest(t_rtv *rtv, t_ray ray,
t_object **close, t_object *current)
{
	t_object		*tmp;
	double			dst;

	tmp = rtv->obj;
	double min = -1;
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

t_vector	obj_norm(t_ray ray, t_object *obj, double dst)
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

t_vector			reflectandrefract(t_ray ray, t_object *obj, t_rtv *rtv, t_hit hit, int depth)
{
	t_vector	normal;
	t_vector	color;
	t_vector 	color2;
	double			ratio[2];
	
	color = (t_vector){0,0,0};
	color2 = (t_vector){0,0,0};
	ray.direction1 = ray.direction;
	ray.direction2 = ray.direction;
	normal = nrm(obj_norm(ray, obj, hit.dst));
	hit.point = add(ray.origin, multi(ray.direction, hit.dst));
	ray.direction1 = add(multi(multi(normal, dot(ray.direction1, normal)), -2.0f), ray.direction1);
	ray.direction2 = add(multi(multi(normal, dot(ray.direction2, normal)), 0.5f), ray.direction2);
	ray.origin = hit.point;
	depth--;
	ratio[0] = obj->reflection+0.1;
	ratio[1] = obj->refraction+0.1;
	if (obj->reflection)
		color = multi(get_pxladv(rtv, ray, ray.direction1,depth), ratio[0]);
	// else{
	// 	color = obj->color;
	// 	ratio[0] = 0.5;
	// }
	if (obj->refraction)
		color2 = multi(get_pxladv(rtv, ray, ray.direction2,depth), ratio[1]);
	// else{
	// 	color2 = obj->color;
	// 	ratio[1] = 0.5;
	// }
	color = divi(color, ratio[0] + ratio[1]);
	color2 = divi(color2, ratio[1] + ratio[0]);
	return(add(color, color2));
}

t_vector			get_pxladv(t_rtv *rtv, t_ray ray, t_vector direction, int depth)
{
	t_hit			hit;
	t_object		*obj;
	t_object		*current;
	t_vector		color;

	obj = NULL;
	current = NULL;
	color = (t_vector){0, 0, 0};
	ray.direction = direction;
	//printf("thi is [%p] \n",getpx);
	if ((hit.dst = get_dest(rtv, ray, &obj, current)) <= 0)
		return (color);
	hit.point = add(ray.origin, multi(direction, hit.dst));
	if (hit.dst > 0)
		color = obj->color;
	if (rtv->light)
		color = lighting(rtv, obj,\
		obj_norm(ray, obj, hit.dst), hit.point, ray);
		// printf("refle is %d\n", getpx->refle);
	if (depth > 0)
		color = reflectandrefract(ray, obj, rtv, hit, depth);
	return (color);
}



t_vector			get_pxl(t_rtv *rtv, t_ray ray, t_getpx *getpx)
{
	t_hit			hit;
	t_object		*obj;
	t_object		*current;
	t_vector		color;
	t_vector		colorini;
	int				depth;

	obj = NULL;
	current = NULL;
	depth = 5;
	color = (t_vector){0, 0, 0};
	colorini = (t_vector){0, 0, 0};
	//printf("thi is [%p] \n",getpx);
	if ((hit.dst = get_dest(rtv, ray, &obj, current)) <= 0)
		return (color);
	hit.point = add(ray.origin, multi(ray.direction, hit.dst));
	if (hit.dst > 0)
		colorini = obj->color;
	if (rtv->light)
		colorini = lighting(rtv, obj,\
		obj_norm(ray, obj, hit.dst), hit.point, ray);
	
	if (depth > 0)
	{
		color = reflectandrefract(ray, obj, rtv, hit, depth);
	}
	colorini = add(colorini, color);
	colorini = divi(colorini, 2);
	return (color);
}


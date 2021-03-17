/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pxl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 10:02:17 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/17 19:29:16 by babdelka         ###   ########.fr       */
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
		if (dst > 0 && (dst < min + 0.01 || min == -1))
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

t_vector			reflectandrefract(t_ray ray, t_object *obj, t_rtv *rtv, t_hit hit)
{
	t_vector	normal;
	t_vector	color;
	
	color = (t_vector){0,0,0};
	ray.direction1 = ray.direction;
	ray.direction2 = ray.direction;
	normal = nrm(obj_norm(ray, obj, hit.dst));
	hit.point = add(ray.origin, multi(ray.direction, hit.dst));
	ray.direction1 = add(multi(multi(normal, dot(ray.direction1, normal)), -2.0f), ray.direction1);
	ray.direction2 = add(multi(multi(normal, dot(ray.direction2, normal)), 0.3f), ray.direction2);
	ray.origin = hit.point;
	color = get_pxladv(rtv, ray, ray.direction1);
	return(color);
}

t_vector			get_pxladv(t_rtv *rtv, t_ray ray, t_vector direction)
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
	if ((obj->type == CONE || obj->type == CYLINDER || obj->type == SPHERE)){
		// printf("refle is %d\n", getpx->refle);
		color = reflectandrefract(ray, obj, rtv, hit);
	}
	return (color);
}



t_vector			get_pxl(t_rtv *rtv, t_ray ray, t_getpx *getpx)
{
	t_hit			hit;
	t_object		*obj;
	t_object		*current;
	t_vector		color;

	obj = NULL;
	current = NULL;
	color = (t_vector){0, 0, 0};
	//printf("thi is [%p] \n",getpx);
	if ((hit.dst = get_dest(rtv, ray, &obj, current)) <= 0)
		return (color);
	hit.point = add(ray.origin, multi(ray.direction, hit.dst));
	if (hit.dst > 0)
		color = obj->color;
	if (rtv->light)
		color = lighting(rtv, obj,\
		obj_norm(ray, obj, hit.dst), hit.point, ray);
	if ((obj->type == CONE || obj->type == CYLINDER || obj->type == SPHERE)){
		// printf("refle is %d\n", getpx->refle);
		color = reflectandrefract(ray, obj, rtv, hit);
	}
	return (color);
}

// t_vector			get_pxl(t_rtv *rtv, t_ray ray, t_blur blur)
// {
// 	double			dst_min;
// 	t_object		*obj;
// 	t_vector		hit_point;
// 	t_vector		color;
// 	t_vector		lastcolor;
// 	t_object		*current;
// 	double			random[3];		
// 	int i = 1;
// 	int b = 0;

// 	obj = NULL;
// 	current = NULL;
// 	color = (t_vector){0, 0, 0};
// 	lastcolor = color;
// 	if ((dst_min = get_dest(rtv, ray, &obj, current)) < 0)
// 		return (color);
// 	// if ((dst_min >= 100))
// 	// 	random[0] = dst_min/100;

// 	// else
// 		random[0] = 2.0;
// 	while (i < 10){
// 			random[1] = (float)rand()/((float)RAND_MAX/random[0]);
// 			random[2] = -(float)rand()/((float)RAND_MAX/random[0]);
// 		ray.direction = nrm(camera(rtv->camera, blur.x+random[1], blur.y+random[2], blur.up));
// 		dst_min = get_dest(rtv, ray, &obj, current);
// 		hit_point = add(ray.origin, multi(ray.direction, dst_min));
// 		if (dst_min > 0)
// 			color = add(color, multi(obj->color, 0.50));
// 		if (rtv->light)
// 			color = add(color, multi(lighting(rtv, obj, obj_norm(ray, obj, dst_min), hit_point, ray), 0.50));
// 		i++;
// 		b++;
// 		// color = add(color, lastcolor);
// 		}
// 	color = multi(color, 0.060);
// 	return(color);
// }

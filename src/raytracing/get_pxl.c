/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pxl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 10:02:17 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/15 12:59:02 by babdelka         ###   ########.fr       */
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
		if (dst > 0 && (dst < min + 0.000001 || min == -1))
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
	return (nrm(normal));
}

t_vector			get_pxl(t_rtv *rtv, t_ray ray, t_blur blur)
{
	double			dst_min;
	t_object		*obj;
	t_vector		hit_point;
	t_vector		color;
	t_vector		lastcolor;
	t_object		*current;
	double				random;
	int i = 1;
	int b = 0;

	obj = NULL;
	current = NULL;
	color = (t_vector){0, 0, 0};
	if ((dst_min = get_dest(rtv, ray, &obj, current)) < 0)
		return (color);
	if (!(dst_min >= 0 && dst_min <=30)){
		while (i < 15){
		if (b == 4 || b == 0){
			random = (float)rand()/((float)RAND_MAX/3);
			b = 0;
		}
		// if (random > 10)
		// 	random *= -1;
		// printf("%f\n", random);
		if (b == 0)
			ray.direction = nrm(camera(rtv->camera, blur.x+random, blur.y, blur.up));
		if (b == 2)
		 	ray.direction = nrm(camera(rtv->camera, blur.x, blur.y+random, blur.up));
		if (b == 1)
			ray.direction = nrm(camera(rtv->camera, blur.x, blur.y-random, blur.up));
		if (b == 3)
		 	ray.direction = nrm(camera(rtv->camera, blur.x-random, blur.y, blur.up));
		if ((dst_min = get_dest(rtv, ray, &obj, current)) < 0)
			color = multi(color, 0.50);
		hit_point = add(ray.origin, multi(ray.direction, dst_min));
		if (dst_min > 0)
			color = add(color, multi(obj->color, 0.10));
		if (rtv->light)
			color = lighting(rtv, obj, obj_norm(ray, obj, dst_min), hit_point, ray);
		i++;
		b++;
		}
		color = multi(add(color, lastcolor), 0.5);
		lastcolor = (multi(add(color, lastcolor), 0.5));
	}
	// else{
	// hit_point = add(ray.origin, multi(ray.direction, dst_min));
	// if (dst_min > 0){
	// 	color = obj->color;
	// 	if (rtv->light)
	// 		color = lighting(rtv, obj_norm(ray, obj, dst_min), hit_point, ray);
	// }
	// rtv->mlx.img[(WIN_H - 1 - (int)rtv->y) * WIN_W + (int)rtv->x] = rgb_to_int(color);
	// }
	
	// hit_point = add(ray.origin, multi(ray.direction, dst_min));
	// if (dst_min > 0)
	// 	color = obj->color;
	// if (rtv->light)
	// {
	// 	color = lighting(rtv, obj, obj_norm(ray, obj, dst_min), hit_point, ray);
	// }
	// return (color);
}

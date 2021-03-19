/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pxl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-el- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 10:02:17 by yait-el-          #+#    #+#             */
/*   Updated: 2021/02/23 10:02:33 by yait-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double				get_dest(t_rtv *rtv, t_ray ray,
t_object **close, t_object *current)
{
	t_object		*tmp;
	double			dst;
	t_vector		xvec;
	t_vector		p_c;
	double			ap = 1;
	double			aps = 1;
	t_quadratic		q;
	double			dst_nega_min = -1;
	double			dst_nega_max = -1;
	int 			shadows;

	t_quadratic		mq;

	tmp = rtv->obj;
	double min = -1;
	while (tmp)
	{	
		if	(tmp->negative == 1)
			{
				if (tmp->type == SPHERE)
					mq = intersection_sphere(ray, *tmp);
				else if (tmp->type == CYLINDER)
					mq = intersection_cylinder(ray, *tmp);
				else if (tmp->type == CONE)
					mq = intersection_cone(ray, *tmp);
				dst_nega_min =  min_ray(mq.t0, mq.t1);
				dst_nega_max = mq.t0 == dst_nega_min ? mq.t1 : mq.t0;

			}
		tmp = tmp->next;
	}

	tmp = rtv->obj;
	shadows = 0;
	while (tmp)
	{
		
		if (tmp->type == SPHERE)
			q = intersection_sphere(ray, *tmp);
		else if (tmp->type == PLANE) 
			dst = intersection_plane(ray, *tmp);
		else if (tmp->type == CYLINDER)
			q = intersection_cylinder(ray, *tmp);
		else if (tmp->type == CONE)
			q = intersection_cone(ray, *tmp);
		if (tmp->type != PLANE)
		{
			dst = min_ray(q.t0, q.t1);
		// 	//closer = dst;
		// 	xvec = sub(ray.origin, (t_vector) {0, 20, 0});
		// 	p_c = add(xvec, multi(ray.direction, dst));
		// 	ap = dot(p_c, (t_vector) {1, -1,0});
		// 	closer = dot(p_c, (t_vector) {1, -1,0});;
		// 	if (ap < 0)
		// 	{
		// 		dst = q.t0 == dst ? q.t1 : q.t0;
		// 		xvec = sub(ray.origin, (t_vector) {0 , 20, 0});
		// 		p_c = add(xvec, multi(ray.direction, dst));
		// 		ap = dot(p_c, (t_vector) {1, -1,0});
		// 		shadows = ap > 0;
		// 	}
		// }
		// else
		// {
		// 	xvec = sub(ray.origin, (t_vector) {0, 20, 0});
		// 	p_c = add(xvec, multi(ray.direction, dst));
		// 	ap = dot(p_c, (t_vector) {1, -1,0});
		}
		if (dst > 0 && ap > 0 && (dst < min + 0.000000001 || min == -1) && tmp->negative != 1)
		{
			if(!(dst > dst_nega_min && dst < dst_nega_max))
			{
				min =  dst;
				*close = tmp;
			}
			else
			{
				dst = q.t0 == dst ? q.t1 : q.t0;
				if((dst < dst_nega_min || dst > dst_nega_max) && tmp->type != PLANE)
				{
					min =  dst;
					*close = tmp;
					shadows = 1;
				}
				else
				{
					shadows = 0;
				}
				
			}
			// if( tmp->negative == 1)
			// {
			// 	dst_nega = dst;
			// 	mq  = q;
			// }
			// else
			// {
			// 	*close = tmp;
			// 	min = dst;
			// }
		}
		tmp = tmp->next;
	}

	if (current != NULL && *close == current)
			return (-1);

	
	// if(dst_nega != -1 && dst_nega < min)
	//   	return -1;
	return min;
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
	//obj->normal = nrm(normal);
	return (nrm(normal));
}

t_vector       ft_reflect(t_vector	color, t_rtv *rtv, t_ray ray, t_object *obj, double dst_min)
{
    int         refle = 0;
    float       var = 0.20f;
	t_vector		hit_point;
	t_vector		normal;

	if(obj->type == PLANE)
	{
		hit_point = add(ray.origin, multi(ray.direction, dst_min));
    	normal = obj_norm(ray, obj, dst_min);
    	ray.direction = add(multi(normal, -2.0 * dot(ray.direction, normal)),ray.direction);
    	ray.origin = hit_point;
		dst_min = get_dest(rtv, ray, &obj, NULL );
		hit_point = add(ray.origin, multi(ray.direction, dst_min));
		int i = 0;
		if (dst_min != -1)
			return lighting(rtv, obj, obj_norm(ray, obj, dst_min), hit_point, ray);
		else
			return color;
	}
    return (color);
}

t_vector			get_pxl(t_rtv *rtv, t_ray ray)
{
	double			dst_min;
	t_object		*obj;
	t_vector		hit_point;
	t_vector		color;
	t_object		*current;

	obj = NULL;
	current = NULL;
	color = (t_vector){0, 0, 0};
	if ((dst_min = get_dest(rtv, ray, &obj, current)) < 0)
		return (color);
	hit_point = add(ray.origin, multi(ray.direction, dst_min));
	if (rtv->light)
	{	
		color = lighting(rtv, obj, obj_norm(ray, obj, dst_min), hit_point, ray);
		//color = ft_reflect(color, rtv, ray, obj, dst_min);
	}
 	return (color);
}

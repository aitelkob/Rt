/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pxl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 10:02:17 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/20 15:13:13 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <math.h>

t_quadratic intersection(t_rtv *rtv,t_ray ray,t_object tmp)
{
	t_quadratic		q;

	if (tmp.type == SPHERE)
		q = intersection_sphere(ray, tmp);
	else if (tmp.type == PLANE) 
		q.t0 = intersection_plane(ray, tmp);
	else if (tmp.type == TRIANGLE) 
		q = intersection_triangle(ray, tmp);

	else if (tmp.type == CYLINDER)
		q = intersection_cylinder(ray, tmp);
	else if (tmp.type == CONE)
		q = intersection_cone(ray, tmp);
	return q;
}

int isnegativeobj(t_rtv *rtv, t_ray ray, double dst)
{
	t_object		*tmp;
	t_quadratic		q;

	tmp = rtv->obj;
	while (tmp)
	{	
		if(tmp->negative == 1)
		{
			q = intersection(rtv, ray, *tmp); 
			if((dst > q.t0 && dst < q.t1))
				return 0;
		}
		tmp = tmp->next;
	}
	return 1;
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
		q = intersection(rtv, ray, *tmp); 
		if (q.t0 > 0 && (q.t0 < min + 0.000000001 || min == -1) && tmp->negative != 1)
		{
			if((isnegativeobj(rtv, ray, q.t0) || (isnegativeobj(rtv, ray, q.t1) && tmp->type != PLANE && tmp->type != TRIANGLE)))
			{
				if(isnegativeobj(rtv, ray, q.t0))
					min = q.t0;
				else
					min = q.t1;
				*close = tmp;
			}
		}
		tmp = tmp->next;
	}
	if (current != NULL && *close == current)
		return (-1);
	return (min);
}

t_min_obj				get_dest_obj(t_rtv *rtv, t_ray ray,
t_object **close, t_object *current)
{
	t_object		*tmp;
	double			min;
	t_quadratic		q;
	t_min_obj		mq;

	min = -1;
	tmp = rtv->obj;
	while (tmp)
	{
		q = intersection(rtv, ray, *tmp); 
		if (q.t0 > 0 && (q.t0 < min + 0.000000001 || min == -1) && tmp->negative != 1)
		{
			if((isnegativeobj(rtv, ray, q.t0) || (isnegativeobj(rtv, ray, q.t1) && tmp->type != PLANE && tmp->type != TRIANGLE)))
			{
				if(isnegativeobj(rtv, ray, q.t0))
					min = q.t0;
				else
					min = q.t1;
				*close = tmp;
				mq.q = q;
			}
		}
		tmp = tmp->next;
	}
	mq.min = min;
	if (current != NULL && *close == current)
		mq.min = -1;;
	return (mq);
}

t_vector			obj_norm(t_ray ray, t_object *obj, double dst)
{
	double			m;
	double			tk;
	t_vector		normal;
	t_vector		p_c;
	t_vector		xvec;

	xvec = sub(ray.origin, obj->origin);
	if (obj->type != PLANE && obj->type != TRIANGLE && obj->type != SPHERE)
		m = dot(ray.direction, obj->aim) * dst + dot(xvec, obj->aim);
	if (obj->type != PLANE && obj->type != TRIANGLE)
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
		normal = crossproduct(sub(obj->c1,obj->origin), sub(obj->c2,obj->origin));
	if (dot(ray.direction, normal) > 0)
		normal = multi(normal, -1);
	return (nrm(normal));
}

t_vector			get_pxl(t_rtv *rtv, t_ray ray)
{
	t_hit			hit;
	t_object		*obj;
	t_vector		color[2];
	double			ratio[2];
	t_min_obj		mq;


	hit.depth = 5;
	color[0] = (t_vector){0, 0, 0};
	color[1] = (t_vector){0, 0, 0};
	mq = get_dest_obj(rtv, ray, &obj, NULL);
	if (mq.min <= 0)
		return (color[0]);
	//return	obj->color;
	hit.point = add(ray.origin, multi(ray.direction, hit.dst));
	if (hit.dst > 0)
		color[0] = obj->color;
	ratio[0] = obj->reflection + 0.2;
	ratio[1] = obj->refraction + 0.2;
	// if (rtv->light)
	// 	color[0] = lighting(rtv, obj, hit, ray);
	// if (hit.depth > 0)
	// 	color[1] = reflectandrefract(ray, obj, rtv, hit);
	// color[1] = divi(finalcolor(color[0], color[1], ratio), 5);
	return (color[0]);
}


// double mod(int i)
// {
// 	return 1.0255 / ;
// }

t_cl_obj			get_pxl_obj(t_rtv *rtv, t_ray ray)
{
	t_hit			hit;
	t_object		*obj;
	t_vector		color[2];
	double			ratio[2];
	t_cl_obj		clr;
	t_min_obj		mq;
	double u;
	double v;


	hit.depth = 5;
	color[0] = (t_vector){0, 0, 0};
	color[1] = (t_vector){0, 0, 0};
	clr.color = color[0];
	clr.obj = obj;
	mq = get_dest_obj(rtv, ray, &obj, NULL);
	if (mq.min <= 0)
		return (clr);
	//return	obj->color;
	hit.dst = mq.min;
	hit.point = add(ray.origin, multi(ray.direction, hit.dst));
	if (hit.dst > 0)
		color[0] = obj->color;
	ratio[0] = obj->reflection + 0.2;
	ratio[1] = obj->refraction + 0.2;
	int x = floor(fmod(hit.point.z,1) * 2);
	int y = floor(fmod(hit.point.x,1) * 2);
	//printf("x == %f, y == %f \n",x , y);
	//int ipos = 0;
	//ipos = 4 * 1000 * y + x * 4;
	
	if(obj->type == 4)
	{ 
		if(fmod(x + y, 2) == 0)
			color[0] = (t_vector){0, 0, 0};
		else
			color[0] = (t_vector){255, 255, 255};
	}
	else if (obj->type == SPHERE)
	{
		u = 1 - (atan2(hit.point.x, hit.point.z)) / (2.0 * PI);
		v = 1 - (acos(hit.point.y / obj->radius)) / PI;
		x = u * 1000;
		y = v * 1000;
		int ipos = 0;
		ipos = 4 * 1000 * y + x * 4;
		color[0] = (t_vector) {rtv->mlx.img_ptr6->buffer[ipos+2] < 0 ? 255 + rtv->mlx.img_ptr6->buffer[ipos+2] : rtv->mlx.img_ptr6->buffer[ipos+2],
		rtv->mlx.img_ptr6->buffer[ipos+1] < 0 ? 255 + rtv->mlx.img_ptr6->buffer[ipos+1] : rtv->mlx.img_ptr6->buffer[ipos+1],
		rtv->mlx.img_ptr6->buffer[ipos] < 0 ? 255 + rtv->mlx.img_ptr6->buffer[ipos+2] : rtv->mlx.img_ptr6->buffer[ipos]};
		//color[0] = (t_vector){0, 0, 0};
		//print_vect(color[0], "color");
		// x = floor(u * 50);
		// y = floor(v * 50);
		// if(fmod(x + y, 2) == 0)
		// 	color[0] = (t_vector){1, 1, 1};
		// else
		// 	color[0] = (t_vector){255, 255, 255};
	}
	if (rtv->light)
	 	color[0] = lightings(color[0] ,rtv, obj, hit, ray);
	
	// if (hit.depth > 0)
	// 	color[1] = reflectandrefract(ray, obj, rtv, hit);
	// color[1] = divi(finalcolor(color[0], color[1], ratio), 5);
	clr.color = color[0];
	clr.obj = obj;
	return (clr);
}
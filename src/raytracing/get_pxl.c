/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pxl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 10:02:17 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/25 12:28:26 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double				slice(t_ray ray, t_quadratic q, t_slice *slice,\
t_object *obj)
{
	t_vector		xvec;
	t_vector		p_c;
	double			is_sliced;
	t_slice			*tmp;

	tmp = slice;
	is_sliced = q.t0;
	while (tmp)
	{
		if (tmp->shape == obj->slicing)
		{
			xvec = sub(ray.origin, tmp->origin);
			p_c = add(xvec, multi(ray.direction, q.t0));
			is_sliced = dot(p_c, tmp->vec) > 0 ? q.t0 : -1;
			if (is_sliced < 0)
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
		if(tmp != current || ray.type == 1)
		{q = intersection(ray, *tmp);
		q.t0 = slice(ray, q, rtv->slice, tmp);
		if (q.t0 > 0 && (q.t0 < min + 0.000000001 ||\
		min == -1) && tmp->negative != 1)
			if ( (isnegativeobj(rtv, ray, q.t0) ||\
			(isnegativeobj(rtv, ray, q.t1) && tmp->type != PLANE)))
			{
				if (isnegativeobj(rtv, ray, q.t0))
					min = q.t0;
				else
					min = q.t1;
				*close = tmp;
			}}
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

void				txtinit(t_txtemp *txt)
{
	txt->x = 0;
	txt->y = 0;
	txt->ipos = 0;
}

void			texture_help(t_rtv *rtv, t_object *obj, t_vector point,\
t_txtemp *txt)
{
	if(obj->type == PLANE)
	{	
		txt->x = fmod((-obj->origin.x - rtv->translationx + point.x)/\
		rtv->scale,1);
		txt->y = fmod((-obj->origin.z - rtv->translationy + point.z)/\
		rtv->scale,1);
	}
	else if(obj->type == SPHERE)
	{	
		txt->x = (1 - ((atan2((obj->origin.x-point.x),\
		obj->origin.z-point.z) / (2.0 * PI)))) + fabs(rtv->translationx/obj->radius);
		txt->y = ((1 - (acos((((obj->origin.y-point.y))/\
		(obj->radius)))) / PI)) + fmod(rtv->translationy,obj->radius) /obj->radius;
	}
	else if(obj->type == CYLINDER || obj->type == CONE)
	{	
		txt->x = (1 - (atan2((-obj->origin.x + point.x) , (-obj->origin.z + \
		point.z))) / (2.0 * PI)) + fabs(rtv->translationx/rtv->scale);
		txt->y = fmod(( point.y) / rtv->scale, 1)  + rtv->translationy/ rtv->scale;
	}
	
}


t_vector	texture_noise(double x, double y,t_vector color)
{
	x = floor(x * 4);
	y = floor(y * 4);
	if(fmod(x + y, 2) == 0)
		return (t_vector){0, 0, 0};
	else
		return color;
}

double min(double a, double b)
{
	return b > a ? a: b;
}

double max(double a, double b)
{
	return b < a ? a: b;
}

t_vector	texture_noise_sine(double x, double y)
{
	t_vector color;
	double tetha  = (5.0 * (x < 0 ? 1+x : x)) / (3.0 * (y < 0 ? 1+y : y)) + PI / 2.0;
	color.x= sin(tetha) * 192 + 128;
   	color.x=max(0,min(255,color.x));
	color.y= sin(tetha -  (2.0 * PI )/3.0) * 192 + 128;
    color.y=max(0,min(255,color.y));
	color.z= sin(tetha -  (4.0 * PI )/3.0) * 192 + 128;
	color.z=max(0,min(255,color.z));
	return color;
}


// t_vector	texture_noise_perlin(double x, double y, t_vector color)
// {
// 	t_vector color;

// 	return color;
// }
int		png_to_rgb(int value)
{
	return value < 0 ? 255 + value: value;
}

t_vector  texture_fromfile(t_rtv *rtv, t_object *obj, t_vector point, t_txtemp txt)
{
	int ipos;
	txt.x = (txt.x < 0 ? 1+txt.x : txt.x) * (obj->w);
	txt.y = (txt.y < 0 ? 1+txt.y : txt.y) * (obj->h);
	ipos = 4 * obj->w * (int) txt.y + (int) txt.x  * 4;
	if(ipos < 4 * obj->img_texture->width * obj->img_texture->height && ipos >= 0) 
		return (t_vector) {
			png_to_rgb(obj->img_texture->buffer[ipos + 2]),
			png_to_rgb(obj->img_texture->buffer[ipos + 1]) ,
			png_to_rgb(obj->img_texture->buffer[ipos])};
	return obj->color;
}

t_vector			texture(t_rtv *rtv, t_object *obj, t_vector point)
{
	t_txtemp txt;

	txtinit(&txt);
	texture_help(rtv, obj, point, &txt);
	int cond = obj->type == PLANE ? point.x > obj->origin.x + rtv->translationx && point.x < obj->origin.x + rtv->translationx + rtv->scale  &&
	point.z > obj->origin.z + rtv->translationy && point.z < obj->origin.z + rtv->translationy + rtv->scale : 1;
	int concylinder =  obj->type == CONE || obj->type == CYLINDER ? point.y > obj->origin.y + rtv->translationy && point.y < obj->origin.y + rtv->translationy + rtv->scale : 1;
	 
		if(obj->disruptions == CHECK)
			return texture_noise_sine(txt.x,txt.y);
			//return texture_noise(txt.x,txt.y, obj->color);
		else if(obj->w != -1)
		{
			if((concylinder && cond ) || obj->type == SPHERE)
				return  texture_fromfile(rtv, obj, point, txt);
		}
	//return multi(obj->color, fmod(random(),10));
	return multi(obj->color,perlin2d((txt.x < 0 ? -txt.x : txt.x), (txt.y < 0 ? -txt.y : txt.y), 100, 4));
}

t_vector			get_pxl(t_rtv *rtv, t_ray ray)
{
	t_hit			hit;
	t_object		*obj;
	t_vector		color[2];
	double			ratio[2];
	t_vector		normal;	
	hit.depth = rtv->camera->depth;
	color[0] = (t_vector){0, 0, 0};
	color[1] = (t_vector){0, 0, 0};
	ray.type = 0;
	if ((hit.dst = get_dest(rtv, ray, &obj, NULL)) <= 0)
		return (color[0]);
	hit.point = add(ray.origin, multi(ray.direction, hit.dst));
	hit.color = obj->color;
	normal = nrm((t_vector) {2 * hit.point.x , 2 * hit.point.z , -1});
	hit.color.x = hit.color.x * normal.x;
	hit.color.y = hit.color.y * normal.y;
	hit.color.z = hit.color.z * normal.z;
	//hit.color = texture(rtv, obj, hit.point);
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

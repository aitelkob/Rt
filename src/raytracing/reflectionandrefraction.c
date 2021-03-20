/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflectionandrefraction.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:39:56 by babdelka          #+#    #+#             */
/*   Updated: 2021/03/20 11:20:13 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void			darkcheck(t_vector *c, double ref)
{
	if (c->x < 20 && c->y < 20 && c->z < 20 && ref > 95)
	{
		c->x = 200;
		c->y = 200;
		c->z = 200;
	}
}

t_vector		finalcolor(t_vector color1, t_vector color2, double *ratio)
{
	t_vector	color;

	color = (t_vector){0, 0, 0};
	color1 = add(color1, multi(color1, (100 - (ratio[0] + ratio[1])) / 100));
	color2 = add(color2, multi(color2, (ratio[0] + ratio[1]) / 100));
	return (add(color1, color2));
}

void			initgp(t_object *obj, t_vector color, t_vector colorini)
{
	obj = NULL;
	color = (t_vector){0, 0, 0};
	colorini = (t_vector){0, 0, 0};
}

t_vector		reflectandrefract(t_ray ray, t_object *obj,\
t_rtv *rtv, t_hit hit)
{
	t_vector	normal;
	t_vector	color[2];
	double		ratio[2];

	color[0] = (t_vector){0, 0, 0};
	color[1] = (t_vector){0, 0, 0};
	ray.direction1 = ray.direction;
	ray.direction2 = ray.direction;
	normal = nrm(obj_norm(ray, obj, hit.dst));
	hit.point = add(ray.origin, multi(ray.direction, hit.dst));
	ray.direction1 = add(multi(multi(normal, dot(ray.direction1, normal)),\
	-2.0f), ray.direction1);
	ray.direction2 = add(multi(multi(normal, dot(ray.direction2, normal)),\
	obj->refractionratio), ray.direction2);
	ray.origin = hit.point;
	hit.depth--;
	ratio[0] = obj->reflection + 0.1;
	ratio[1] = obj->refraction + 0.1;
	if (obj->reflection)
		color[0] = multi(gpxadv(rtv, ray, ray.direction1, hit.depth), ratio[0]);
	if (obj->refraction)
		color[1] = multi(gpxadv(rtv, ray, ray.direction2, hit.depth), ratio[1]);
	color[0] = divi(color[0], ratio[0] + ratio[1]);
	color[1] = divi(color[1], ratio[1] + ratio[0]);
	return (add(color[0], color[1]));
}

t_vector		gpxadv(t_rtv *rtv, t_ray ray, t_vector direction, int depth)
{
	t_hit		hit;
	t_object	*obj;
	t_vector	color;
	t_vector	colorini;
	double		ratio[2];

	initgp(obj, color, colorini);
	ray.direction = direction;
	hit.depth = depth;
	if ((hit.dst = get_dest(rtv, ray, &obj, NULL)) <= 0)
		return (color);
	hit.point = add(ray.origin, multi(direction, hit.dst));
	if (hit.dst > 0)
		colorini = obj->color;
	ratio[0] = obj->reflection + 0.2;
	ratio[1] = obj->refraction + 0.2;
	if (rtv->light)
		colorini = lighting(rtv, obj, hit, ray);
	if (depth > 0)
		color = reflectandrefract(ray, obj, rtv, hit);
	color = divi(finalcolor(colorini, color, ratio), 2);
	return (color);
}

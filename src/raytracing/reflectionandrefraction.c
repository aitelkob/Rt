/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflectionandrefraction.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:39:56 by babdelka          #+#    #+#             */
/*   Updated: 2021/03/27 18:23:15 by babdelka         ###   ########.fr       */
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

t_vector		gpxaddv(t_rtv *rtv, t_ray ray, t_vector direction, t_hit hit)
{
	t_object	*obj;
	t_vector	color[2];
	double		ratio[2];

	color[0] = (t_vector){0, 0, 0};
	color[1] = (t_vector){0, 0, 0};
	ray.direction = direction;
	ray.type = 0;
	if ((hit.dst = get_dest(rtv, ray, &obj, hit.current)) <= 0)
		return (color[0]);
	hit.point = add(ray.origin, multi(direction, hit.dst));
	hit.color = obj->color;
	hit.color = texture(rtv, obj, hit.point);
	if (hit.dst > 0 && rtv->light->intensity == 0)
		color[0] = multi(divi(hit.color, 100), rtv->camera->amblgt);
	ratio[0] = obj->reflection + 0.2;
	ratio[1] = obj->refraction + 0.2;
	if (rtv->light)
		color[0] = lighting(rtv, obj, hit, ray);
	if (hit.depth > 0)
		color[1] = reflectandrefract(ray, obj, rtv, hit);
	color[1] = divi(finalcolor(color[0], color[1], ratio), 2);
	return (color[1]);
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
	hit.current = obj;
	hit.point = add(ray.origin, multi(ray.direction, hit.dst));
	ray.direction1 = add(multi(multi(normal, dot(ray.direction1, normal)),\
	-2.0f), ray.direction1);
	ray.direction2 = add(multi(multi(normal, dot(ray.direction2, normal)),\
	obj->refraratio), ray.direction2);
	ray.origin = hit.point;
	hit.depth--;
	ratio[0] = obj->reflection - 0.85;
	ratio[1] = obj->refraction + 0.1;
	if (obj->reflection)
		color[0] = multi(gpxaddv(rtv, ray, ray.direction1, hit), ratio[0]);
	if (obj->refraction)
		color[1] = multi(gpxaddv(rtv, ray, ray.direction2, hit), ratio[1]);
	return (add(divi(color[0], ratio[0] + ratio[1]),\
	divi(color[1], ratio[1] + ratio[0])));
}

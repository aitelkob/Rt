/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 19:15:32 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/20 15:53:20 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double				shadow(t_light *tmp_light, t_shadowadv *shadv,
t_rtv *rtv, t_object *obj)
{
	t_ray			ray_light;
	t_object		*tmp_obj;
	double			dst;

	ray_light.origin = tmp_light->origin;
	ray_light.direction = nrm(multi(shadv->light_dir, -1));
	dst = get_dest(rtv, ray_light, &tmp_obj, obj);
	if(dst != -1){
		shadv->color = tmp_obj->color;
		shadv->refra = tmp_obj->refraction;
	}
	darkcheck(&shadv->color, shadv->refra);
	return (dst);
}

double				specular(t_vector org_hit, t_vector light_dir,
double dst, t_vector normal)
{
	t_vector		cam_light;

	cam_light = nrm(add(light_dir, org_hit));
	return (dst == -1) * dot(cam_light, normal);
}

double				diffuse(t_vector light_dir, double dst, t_vector normal)
{
	double			alpha;

	alpha = dot(nrm(light_dir), normal);
	return ((!(dst != -1 || alpha < 0)) * alpha);
}

t_vector				color_nrm_vec(t_vector i)
{
	i.x = i.x > 255 ? 255 : i.x;
	i.y = i.y > 255 ? 255 : i.y;
	i.z = i.z > 255 ? 255 : i.z;
	return i;
}
t_vector			coloring(t_vector color, double diffuse,
double specular, t_vector obj_color)
{
	color = color_nrm_vec(add(color, multi(obj_color, 0.1 + diffuse)));
	color = color_nrm_vec(add(color, multi((t_vector) {1, 1, 1},
	diffuse * 255 * powf(specular < 0 ? 0 : specular, 100))));
	return (color);
}

t_vector			lighting(t_rtv *rtv, t_object *obj,\
t_hit hit, t_ray ray)
{
	t_light			*tmp;
	t_shadowadv		shadv;
	t_vector		color;
	double			dst;
	double			spec;

	tmp = rtv->light;
	color = (t_vector) {0, 0, 0};
	hit.normal = nrm(obj_norm(ray, obj, hit.dst));
	while (tmp)
	{
		shadv.light_dir = sub(tmp->origin, hit.point);
		dst = shadow(tmp, &shadv, rtv, obj);
		if (--shadv.refra > 0 && dst > 2)
			color = add(color, multi(shadv.color, (shadv.refra) * (0.00001\
			* tmp->intensity)));
		spec = specular(sub(ray.origin, hit.point), shadv.light_dir, dst,\
		hit.normal);
		color = coloring(color, diffuse(shadv.light_dir, dst, hit.normal) \
		* (tmp->intensity / 100.0), spec,obj->color);
		tmp = tmp->next;
	}
	return (color);
}


t_vector			lightings(t_vector colors,t_rtv *rtv, t_object *obj,\
t_hit hit, t_ray ray)
{
	t_light			*tmp;
	t_shadowadv		shadv;
	t_vector		color;
	double			dst;
	double			spec;

	tmp = rtv->light;
	color = (t_vector) {0, 0, 0};
	hit.normal = nrm(obj_norm(ray, obj, hit.dst));
	while (tmp)
	{
		shadv.light_dir = sub(tmp->origin, hit.point);
		dst = shadow(tmp, &shadv, rtv, obj);
		if (--shadv.refra > 0 && dst > 2)
			color = add(color, multi(shadv.color, (shadv.refra) * (0.00001\
			* tmp->intensity)));
		spec = specular(sub(ray.origin, hit.point), shadv.light_dir, dst,\
		hit.normal);
		color = coloring(color, diffuse(shadv.light_dir, dst, hit.normal) \
		* (tmp->intensity / 100.0), spec, colors);
		tmp = tmp->next;
	}
	return (color);
}
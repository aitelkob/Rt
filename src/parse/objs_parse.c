/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objs_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 17:05:31 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/19 10:07:32 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void					convertmaterial(t_object *obj)
{
	if (obj->material == MIRROR)
	{
		obj->reflection = 100;
		obj->refraction = 0;
		obj->color = (t_vector){0,0,0};
	}
	if (obj->material == GLASS)
	{
		obj->refraction = 100;
		obj->reflection = 0;
		obj->refractionratio = 1;
		obj->color = (t_vector){0,0,0};
	}
	if (obj->material == RAWMETAL)
	{
		obj->reflection = 0;
		obj->refraction = 0;
	}
	if (obj->material == WATER)
	{
		obj->reflection = 0;
		obj->refraction = 100;
		obj->refractionratio = 0.62;
		obj->color = (t_vector){100,100,200};
	}
}

void					plan_parce(t_rtv *rtv)
{
	static	t_object	*plan;
	char				*arg;
	char				*data;

	if (!plan)
	{
		if (!(plan = (t_object *)malloc(sizeof(t_object))))
			error("obj error allocat", "just alloct");
		init_obj(plan);
	}
	plan->type = PLANE;
	rtv->parse.nb_line++;
	if (get_next_line(rtv->parse.fd, &data) == 1 && data[0] == ' ')
	{
		data = settings_cut(rtv, data, &arg);
		plan_checker(data, arg, plan, rtv);
		convertmaterial(plan);
		plan_parce(rtv);
	}
	else
	{
		rot_trans(plan);
		first_obj(rtv, plan);
		plan = NULL;
		forward(rtv, data);
	}
}

void					sphere_parce(t_rtv *rtv)
{
	static	t_object	*sphere;
	char				*data;
	char				*arg;

	if (!sphere)
	{
		if (!(sphere = (t_object *)malloc(sizeof(t_object))))
			error("obj error allocat", "just alloct");
		init_obj(sphere);
	}
	sphere->type = SPHERE;
	rtv->parse.nb_line++;
	if (get_next_line(rtv->parse.fd, &data) == 1 && data[0] == ' ')
	{
		data = settings_cut(rtv, data, &arg);
		sphere_checker(data, arg, sphere, rtv);
		convertmaterial(sphere);
		sphere_parce(rtv);
	}
	else
	{
		sphere->origin = add(sphere->origin, sphere->translation);
		first_obj(rtv, sphere);
		sphere = NULL;
		forward(rtv, data);
	}
}

void					cylinder_parce(t_rtv *rtv)
{
	static	t_object	*cylinder;
	char				*data;
	char				*arg;

	if (!cylinder)
	{
		if (!(cylinder = (t_object *)malloc(sizeof(t_object))))
			error("obj error allocat", "just alloct");
		init_obj(cylinder);
	}
	cylinder->type = CYLINDER;
	rtv->parse.nb_line++;
	if (get_next_line(rtv->parse.fd, &data) == 1 && data[0] == ' ')
	{
		data = settings_cut(rtv, data, &arg);
		cylinder_checker(data, arg, cylinder, rtv);
		convertmaterial(cylinder);
		cylinder_parce(rtv);
	}
	else
	{
		rot_trans(cylinder);
		first_obj(rtv, cylinder);
		cylinder = NULL;
		forward(rtv, data);
	}
}

void					cone_parce(t_rtv *rtv)
{
	static	t_object	*cone;
	char				*data;
	char				*arg;

	if (!cone)
	{
		if (!(cone = (t_object *)malloc(sizeof(t_object))))
			error("obj error allocat", "just alloct");
		init_obj(cone);
	}
	cone->type = CONE;
	rtv->parse.nb_line++;
	if (get_next_line(rtv->parse.fd, &data) == 1 && data[0] == ' ')
	{
		data = settings_cut(rtv, data, &arg);
		cone_checker(data, arg, cone, rtv);
		convertmaterial(cone);
		cone_parce(rtv);
	}
	else
	{
		rot_trans(cone);
		first_obj(rtv, cone);
		cone = NULL;
		forward(rtv, data);
	}
}

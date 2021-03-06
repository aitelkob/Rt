/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objs_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 17:05:31 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/21 18:00:38 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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

void					triangle_parce(t_rtv *rtv)
{
	static	t_object	*triangle;
	char				*arg;
	char				*data;

	if (!triangle)
	{
		if (!(triangle = (t_object *)malloc(sizeof(t_object))))
			error("obj error allocat", "just alloct");
		init_obj(triangle);
	}
	triangle->type = TRIANGLE;
	rtv->parse.nb_line++;
	if (get_next_line(rtv->parse.fd, &data) == 1 && data[0] == ' ')
	{
		data = settings_cut(rtv, data, &arg);
		triangle_checker(data, arg, triangle, rtv);
		triangle_parce(rtv);
	}
	else
	{
		rot_trans(triangle);
		first_obj(rtv, triangle);
		triangle = NULL;
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

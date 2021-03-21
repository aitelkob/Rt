/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 17:07:15 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/20 18:42:02 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	plan_checker(char *data, char *arg, t_object *plan, t_rtv *rtv)
{
	if (!ft_strcmp("origin", data))
		plan->origin = input_vector(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("aim", data))
		plan->aim = input_vector(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("color", data))
		plan->color = input_vector(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("reflection", data))
		plan->reflection = input_onearg(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("negative", data))
		plan->negative = input_onearg(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("refraction", data))
		plan->refraction = input_onearg(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("refraction_index", data))
		plan->refraction = input_onearg(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("translation", data))
		plan->translation = input_vector(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("rot", data))
		plan->rot = input_vector(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("material", data))
		plan->material = input_material(rtv, arg, rtv->parse.nb_line, data);
	else
	{
		free(data);
		unknown_setting(rtv, "plan", rtv->parse.nb_line);
	}
	free(data);
}

void	triangle_checker(char *data, char *arg, t_object *triangle, t_rtv *rtv)
{
	if (!ft_strcmp("origin", data))
		triangle->origin = input_vector(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("c1", data))
		triangle->c1 = input_vector(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("color", data))
		triangle->color = input_vector(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("negative", data))
		triangle->negative = input_onearg(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("translation", data))
		triangle->translation = input_vector(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("rot", data))
		triangle->c2= input_vector(rtv, arg, rtv->parse.nb_line, data);
	else
	{
		free(data);
		unknown_setting(rtv, "triangle", rtv->parse.nb_line);
	}
	free(data);
}

void	sphere_checker(char *data, char *arg, t_object *sphere, t_rtv *rtv)
{
	if (!ft_strcmp("origin", data))
		sphere->origin = input_vector(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("radius", data))
		sphere->radius = input_onearg(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("reflection", data))
		sphere->reflection = input_onearg(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("refraction", data))
		sphere->refraction = input_onearg(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("refraction_index", data))
		sphere->refraction = input_onearg(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("negative", data))
		sphere->negative = input_onearg(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("color", data))
		sphere->color = input_vector(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("translation", data))
		sphere->translation = input_vector(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("material", data))
		sphere->material = input_material(rtv, arg, rtv->parse.nb_line, data);
	else
	{
		free(data);
		unknown_setting(rtv, "sphere", rtv->parse.nb_line);
	}
	free(data);
}

void	cylinder_checker(char *data, char *arg, t_object *cylinder, t_rtv *rtv)
{
	if (!ft_strcmp("origin", data))
		cylinder->origin = input_vector(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("aim", data))
		cylinder->aim = input_vector(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("radius", data))
		cylinder->radius = input_onearg(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("rot", data))
		cylinder->rot = input_vector(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("reflection", data))
		cylinder->reflection = input_onearg(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("refraction", data))
		cylinder->refraction = input_onearg(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("refraction_index", data))
		cylinder->refraction = input_onearg(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("negative", data))
		cylinder->negative = input_onearg(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("color", data))
		cylinder->color = input_vector(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("translation", data))
		cylinder->translation = input_vector(rtv, arg,
		rtv->parse.nb_line, data);
	else if (!ft_strcmp("material", data))
		cylinder->material = input_material(rtv, arg, rtv->parse.nb_line, data);
	else
	{
		free(data);
		unknown_setting(rtv, "cylinder", rtv->parse.nb_line);
	}
	free(data);
}

void	cone_checker(char *data, char *arg, t_object *cone, t_rtv *rtv)
{
	if (!ft_strcmp("origin", data))
		cone->origin = input_vector(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("aim", data))
		cone->aim = input_vector(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("radius", data))
		cone->radius = input_onearg(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("reflection", data))
		cone->reflection = input_onearg(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("refraction", data))
		cone->refraction = input_onearg(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("refraction_index", data))
		cone->refraction = input_onearg(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("angle", data))
		cone->angle = input_onearg(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("rot", data))
		cone->rot = input_vector(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("negative", data))
		cone->negative = input_onearg(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("color", data))
		cone->color = input_vector(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("translation", data))
		cone->translation = input_vector(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("material", data))
		cone->material = input_material(rtv, arg, rtv->parse.nb_line, data);
	else
	{
		free(data);
		unknown_setting(rtv, "cone", rtv->parse.nb_line);
	}
	free(data);
}

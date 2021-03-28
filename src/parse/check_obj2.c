/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_obj2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 17:49:08 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/27 15:15:26 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		cylinder_help(char *data, char *arg, t_object *cylinder, t_rtv *rtv)
{
	if (!ft_strcmp("-refraction_index", data))
		cylinder->refraratio = input_onearg(arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-negative", data))
		cylinder->negative = input_onearg(arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-color", data))
		cylinder->color = input_vector_color(arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-texture", data))
		cylinder->texture = input_texture(arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-slice", data))
		cylinder->slicing = input_onearg(arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-translation", data))
		cylinder->translation = input_vector(arg,
				rtv->parse.nb_line, data);
	else if (!ft_strcmp("-material", data))
		cylinder->material = input_material(arg, rtv->parse.nb_line, data);
	else
	{
		free(data);
		unknown_setting("cylinder", rtv->parse.nb_line);
	}
}

void		cylinder_checker(char *data, char *arg,
t_object *cylinder, t_rtv *rtv)
{
	if (!ft_strcmp("-origin", data))
		cylinder->origin = input_vector(arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-aim", data))
		cylinder->aim = input_vector(arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-radius", data))
		cylinder->radius = input_radius(arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-rot", data))
		cylinder->rot = input_vector(arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-reflection", data))
		cylinder->reflection = input_onearg(arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-refraction", data))
		cylinder->refraction = input_onearg(arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-disrup", data))
		cylinder->disruptions = input_noise(arg, rtv->parse.nb_line, data);
	else
		cylinder_help(data, arg, cylinder, rtv);
	convertmaterial(cylinder);
	free(data);
}

void		cone_checker_help(char *data, char *arg, t_object *cone, t_rtv *rtv)
{
	if (!ft_strcmp("-angle", data))
		cone->angle = input_onearg(arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-rot", data))
		cone->rot = input_vector(arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-negative", data))
		cone->negative = input_onearg(arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-color", data))
		cone->color = input_vector_color(arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-translation", data))
		cone->translation = input_vector(arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-material", data))
		cone->material = input_material(arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-disrup", data))
		cone->disruptions = input_noise(arg, rtv->parse.nb_line, data);
	else
	{
		free(data);
		unknown_setting("cone", rtv->parse.nb_line);
	}
}

void		cone_checker(char *data, char *arg, t_object *cone, t_rtv *rtv)
{
	if (!ft_strcmp("-origin", data))
		cone->origin = input_vector(arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-aim", data))
		cone->aim = input_vector(arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-radius", data))
		cone->radius = input_radius(arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-reflection", data))
		cone->reflection = input_onearg(arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-slice", data))
		cone->slicing = input_onearg(arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-refraction", data))
		cone->refraction = input_onearg(arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-texture", data))
		cone->texture = input_texture(arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-refraction_index", data))
		cone->refraratio = input_onearg(arg, rtv->parse.nb_line, data);
	else
		cone_checker_help(data, arg, cone, rtv);
	convertmaterial(cone);
	free(data);
}

void		triangle_checker_help(char *data, char *arg, t_object *triangle,\
t_rtv *rtv)
{
	if (!ft_strcmp("-refraction", data))
		triangle->refraction = input_onearg(arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-reflection", data))
		triangle->reflection = input_onearg(arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-refraction_index", data))
		triangle->refraratio = input_onearg(arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-texture", data))
		triangle->texture = input_texture(arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-disrup", data))
		triangle->disruptions = input_noise(arg, rtv->parse.nb_line, data);
	else
	{
		free(data);
		unknown_setting("triangle", rtv->parse.nb_line);
	}
}

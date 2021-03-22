/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 15:22:50 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/22 13:01:33 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void						slice_check(char *data, char *arg,
t_slice *slice, t_rtv *rtv)
{
	if (!ft_strcmp("-origin", data))
		slice->origin = input_vector(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-vec", data))
		slice->vec = input_vector(rtv, arg, rtv->parse.nb_line, data);
	else
	{
		free(data);
		unknown_setting(rtv, "slice", rtv->parse.nb_line);
	}
	free(data);
}

void						camera_check(char *data, char *arg,
t_camera *camera, t_rtv *rtv)
{
	if (!ft_strcmp("-origin", data))
		camera->origin = input_vector(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-fov", data))
		camera->fov = input_onearg(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-look_at", data))
		camera->look_at = input_vector(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-depth", data))
		camera->depth = input_onearg(rtv, arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-ambient_light", data))
		camera->amblgt = input_onearg(rtv, arg, rtv->parse.nb_line, data);
	else
	{
		free(data);
		unknown_setting(rtv, "camera", rtv->parse.nb_line);
	}
	free(data);
}

void						slice_parce(t_rtv *rtv)
{
	static	t_slice			*slice;
	char					*data;
	char					*arg;

	if (!slice)
		if (!(slice = (t_slice *)malloc(sizeof(t_slice))))
			error("obj error allocat", "just alloct");
	rtv->parse.nb_line++;
	if (get_next_line(rtv->parse.fd, &data) == 1 && data[0] == ' ')
	{
		data = settings_cut(rtv, data, &arg);
		slice_check(data, arg, slice, rtv);
		slice_parce(rtv);
	}
	else
	{
		first_slice(rtv, slice);
		slice = NULL;
		forward(rtv, data);
	}
}

void						light_parce(t_rtv *rtv)
{
	static	t_light			*light;
	char					*data;
	char					*arg;

	if (!light)
	{
		if (!(light = (t_light *)malloc(sizeof(t_light))))
			error("obj error allocat", "just alloct");
		light->intensity = 100;
	}
	rtv->parse.nb_line++;
	if (get_next_line(rtv->parse.fd, &data) == 1 && data[0] == ' ')
	{
		data = settings_cut(rtv, data, &arg);
		light_check(data, arg, light, rtv);
		light_parce(rtv);
	}
	else
	{
		first_light(rtv, light);
		light = NULL;
		forward(rtv, data);
	}
}

void						camera_parce(t_rtv *rtv)
{
	static	t_camera		*camera;
	char					*data;
	char					*arg;

	if (!camera)
	{
		if (!(camera = (t_camera *)malloc(sizeof(t_camera))))
			error("obj error allocat", "just alloct");
		init_cam(camera);
	}
	rtv->parse.nb_line++;
	if (get_next_line(rtv->parse.fd, &data) == 1 && data[0] == ' ')
	{
		data = settings_cut(rtv, data, &arg);
		camera_check(data, arg, camera, rtv);
		camera_parce(rtv);
	}
	else
	{
		rtv->camera = camera;
		rtv->camera->check = 1;
		camera = NULL;
		forward(rtv, data);
	}
}

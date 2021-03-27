/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 15:22:50 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/27 15:19:10 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void						slice_check(char *data, char *arg,
t_slice *slice, t_rtv *rtv)
{
	if (!ft_strcmp("-origin", data))
		slice->origin = input_vector(arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-vec", data))
		slice->vec = input_vector(arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-shape", data))
		slice->shape = input_onearg(arg, rtv->parse.nb_line, data);
	else
	{
		free(data);
		unknown_setting("slice", rtv->parse.nb_line);
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

void						first_cam(t_rtv *rtv, t_camera *camera)
{
	t_camera		*tmp;

	tmp = camera;
	tmp->next = rtv->camera;
	rtv->camera = tmp;
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
		first_cam(rtv, camera);
		camera = NULL;
		rtv->camera->check = 1;
		forward(rtv, data);
	}
}

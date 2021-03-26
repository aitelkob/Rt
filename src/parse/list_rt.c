/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 18:13:58 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/24 19:12:04 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				first_obj(t_rtv *rtv, t_object *obj)
{
	t_object		*tmp;

	tmp = obj;
	tmp->next = rtv->obj;
	rtv->obj = tmp;
}

void				first_slice(t_rtv *rtv, t_slice *slice)
{
	t_slice			*tmp;

	tmp = slice;
	tmp->next = rtv->slice;
	rtv->slice = tmp;
}

void				first_light(t_rtv *rtv, t_light *light)
{
	t_light			*tmp;

	tmp = light;
	tmp->next = rtv->light;
	rtv->light = tmp;
}

void				init_cam(t_camera *cam)
{
	cam->fov = 60;
	cam->depth = 5;
	cam->look_at = (t_vector){0, 0, 0};
	cam->amblgt = 25;
	cam->next = NULL;
}

void				light_check(char *data, char *arg,
t_light *light, t_rtv *rtv)
{
	if (!ft_strcmp("-origin", data))
		light->origin = input_vector(arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-intensity", data))
		light->intensity = input_onearg(arg, rtv->parse.nb_line, data);
	else
	{
		free(data);
		unknown_setting("light", rtv->parse.nb_line);
	}
	free(data);
}

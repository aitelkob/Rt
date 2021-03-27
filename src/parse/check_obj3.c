/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_obj3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 15:16:17 by babdelka          #+#    #+#             */
/*   Updated: 2021/03/27 15:47:17 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void						camera_check(char *data, char *arg,
t_camera *camera, t_rtv *rtv)
{
	if (!ft_strcmp("-origin", data))
		camera->origin = input_vector(arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-fov", data))
		camera->fov = input_onearg(arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-look_at", data))
		camera->look_at = input_vector(arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-depth", data))
		camera->depth = input_onearg(arg, rtv->parse.nb_line, data);
	else if (!ft_strcmp("-ambient", data))
		camera->amblgt = input_onearg(arg, rtv->parse.nb_line, data);
	else
	{
		free(data);
		unknown_setting("camera", rtv->parse.nb_line);
	}
	free(data);
}
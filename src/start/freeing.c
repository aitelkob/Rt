/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 15:39:37 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/27 16:12:52 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			free_objects(t_rtv *rtv)
{
	t_object	*next;

	while (rtv && rtv->obj)
	{
		next = rtv->obj->next;
		free(rtv->obj);
		rtv->obj = next;
	}
}

void			free_slice(t_rtv *rtv)
{
	t_slice	*next;

	while (rtv && rtv->slice)
	{
		next = rtv->slice->next;
		free(rtv->slice);
		rtv->slice = next;
	}
}

void			free_lights(t_rtv *rtv)
{
	t_light		*next;

	while (rtv && rtv->light)
	{
		next = rtv->light->next;
		free(rtv->light);
		rtv->light = next;
	}
}

void			free_cameras(t_rtv *rtv)
{
	t_camera		*next;

	while (rtv && rtv->camera)
	{
		next = rtv->camera->next;
		free(rtv->camera);
		rtv->camera = next;
	}
}

void			exiting_program(t_rtv *rtv)
{
	ft_destroy(&rtv->mlx);
	if (rtv->camera)
		free_cameras(rtv);
	if (rtv->light)
		free_lights(rtv);
	if (rtv->obj)
		free_objects(rtv);
	if (rtv->slice)
		free_lights(rtv);
	exit(0);
}

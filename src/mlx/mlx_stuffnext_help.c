/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_stuffnext_help.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 15:16:45 by babdelka          #+#    #+#             */
/*   Updated: 2021/03/24 18:40:48 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			camfocal_help(int keycode, t_rtv *rtv)
{
    if (keycode == 69)
	{
		displayloading(&rtv->mlx);
		rtv->camera->origin.z += 10;
		raytracing(*rtv);
		display(rtv, &rtv->mlx);
	}
	if (keycode == 78)
	{
		displayloading(&rtv->mlx);
		rtv->camera->origin.z -= 10;
		raytracing(*rtv);
		display(rtv, &rtv->mlx);
	}

}
void			camfocal(int keycode, t_rtv *rtv)
{
	if (keycode == 92 && rtv->camera->fov < 120)
	{
		displayloading(&rtv->mlx);
		rtv->camera->fov += 10;
		raytracing(*rtv);
		display(rtv, &rtv->mlx);
	}
	if (keycode == 89 && rtv->camera->fov > 40)
	{
		displayloading(&rtv->mlx);
		rtv->camera->fov -= 10;
		raytracing(*rtv);
		display(rtv, &rtv->mlx);
	}
	camfocal_help(keycode, rtv);
}
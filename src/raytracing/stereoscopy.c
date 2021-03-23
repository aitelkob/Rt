/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stereoscopy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 10:34:17 by yait-el-          #+#    #+#             */
/*   Updated: 2021/03/23 11:59:45 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int					isblack(t_vector color)
{
	if (color.x == 0 && color.x == 0 && color.x == 0 )
		return(1);
	else
		return(0);
}

void				stereoscopy(t_rtv *rtv, double x, double y, t_ray ray2)
{
	int				i;
	t_vector		test;
	t_vector		color;
	t_vector		color2;
	t_vector		up;

	color = (t_vector){0, 0, 0};
	color2 = (t_vector){0, 0, 0};
	test = (t_vector){0, 0, 0};
	i = 0;
	ray2.direction = nrm(camera(rtv->camera, x + 15, y, test));
	color = get_pxl(rtv, ray2);
	if (!isblack(color))
	{
		color.y = 0;
		color.x+= 60;
	}
	ray2.direction = nrm(camera(rtv->camera, x - 15, y, test));
	color2 = get_pxl(rtv, ray2);
	if (!isblack(color2))
	{
		color2.x = 0;
		color2.y += 60;
	}
	color.x = (color.x + color2.x) / 2;
	color.y = (color.y + color2.y) / 2;
	color.z = (color.z + color2.z) / 2;
	rtv->mlx.img[(WIN_H - 1 - (int)y) * WIN_W + (int)x] = rgb_to_int(color);
}
